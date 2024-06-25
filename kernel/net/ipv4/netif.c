/**
 * @author Ali Mirmohammad
 * @file netif.c
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - Kernel net interface for the IPV4 driver.
*/
#include <net/netif.h>
#include <net/opt.h>
#include <net/etharp.h>
#include <net/tcp.h>
#include <net/tcp_impl.h>
#include <alinix/ip.h>
#include <alinix/arch.h>
#include <net/def.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("AliNix IPV4 driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

/**
 * @brief Useful macro for callback.
 */
#define NETIF_STATUS_CALLBACK(n)


struct netif *netif_list;

/**
 * Set the NETIF_FLAG_UP flag for a network interface, indicating that it is up and ready to transmit and receive packets.
 *
 * @param netif The network interface to set up.
 *
 * @note This function sets the NETIF_FLAG_UP flag for the given network interface, indicating that it is up and ready to transmit and receive packets.
 *       If the NETIF_FLAG_UP flag is already set, the function does nothing.
 *       If the NETIF_FLAG_UP flag is not set, the function sets it and performs the following actions:
 *       - Sets the NETIF_FLAG_LINK_UP flag if it is set for the network interface.
 *       - Sends a "gratuitous ARP" message for Ethernet network interfaces if the NETIF_FLAG_ETHARP flag is set.
 *       - Resends IGMP memberships for the network interface if the NETIF_FLAG_IGMP flag is set.
 *       - Calls the NETIF_STATUS_CALLBACK function for the network interface.
 *
 * @see NETIF_FLAG_UP, NETIF_FLAG_LINK_UP, NETIF_FLAG_ETHARP, NETIF_FLAG_IGMP, NETIF_STATUS_CALLBACK
 */
void netif_set_up(struct netif *netif)
{
  if (!(netif->flags & NETIF_FLAG_UP)) {
    netif->flags |= NETIF_FLAG_UP;
    
#if LWIP_SNMP
    snmp_get_sysuptime(&netif->ts);
#endif /* LWIP_SNMP */

    NETIF_STATUS_CALLBACK(netif);

    if (netif->flags & NETIF_FLAG_LINK_UP) {
#if LWIP_ARP
      /* For Ethernet network interfaces, we would like to send a "gratuitous ARP" */ 
      if (netif->flags & (NETIF_FLAG_ETHARP)) {
        etharp_gratuitous(netif);
      }
#endif /* LWIP_ARP */

#if LWIP_IGMP
      /* resend IGMP memberships */
      if (netif->flags & NETIF_FLAG_IGMP) {
        igmp_report_groups( netif);
      }
#endif /* LWIP_IGMP */
    }
  }
}

/**
 * Set the NETIF_FLAG_DOWN flag for a network interface, indicating that it is down and not ready to transmit or receive packets.
 *
 * @param netif The network interface to set down.
 *
 * @note This function sets the NETIF_FLAG_DOWN flag for the given network interface, indicating that it is down and not ready to transmit or receive packets.
 *       If the NETIF_FLAG_UP flag is not set, the function does nothing.
 *       If the NETIF_FLAG_UP flag is set, the function clears it and performs the following actions:
 *       - Sets the NETIF_FLAG_LINK_DOWN flag if it is set for the network interface.
 *       - Cleans up ARP entries for Ethernet network interfaces if the NETIF_FLAG_ETHARP flag is set.
 *       - Calls the NETIF_STATUS_CALLBACK function for the network interface.
 *
 * @see NETIF_FLAG_DOWN, NETIF_FLAG_LINK_DOWN, NETIF_FLAG_ETHARP, NETIF_STATUS_CALLBACK
 */
void netif_set_down(struct netif *netif)
{
  if (netif->flags & NETIF_FLAG_UP) {
    netif->flags &= ~NETIF_FLAG_UP;
#if LWIP_SNMP
    snmp_get_sysuptime(&netif->ts);
#endif /*LWIP_SNMP*/

#if LWIP_ARP
    if (netif->flags & NETIF_FLAG_ETHARP) {
      etharp_cleanup_netif(netif);
    }
#endif /* LWIP_ARP */
    NETIF_STATUS_CALLBACK(netif);
  }
}


/**
 * Set the IP address of a network interface.
 *
 * @param netif The network interface to set the IP address for.
 * @param ipaddr The new IP address to set.
 *
 * @note This function sets the IP address of the given network interface to the specified IP address.
 *       If the IP address is already set to the same value, the function does nothing.
 *       If the IP address is being changed, the function performs the following actions:
 *       - Aborts all active TCP connections that are bound to the current local interface address.
 *       - Updates the listening TCP PCBs to listen on the new IP address.
 *       - Deletes and re-inserts the IP address index and route index trees in the SNMP subsystem.
 *       - Sets the new IP address for the network interface.
 *       - Prints a debug message indicating the new IP address.
 *
 * @see ip_addr_t
 */
void
netif_set_ipaddr(struct netif *netif, ip_addr_t *ipaddr)
{
  /* TODO: Handling of obsolete pcbs */
  /* See:  http://mail.gnu.org/archive/html/lwip-users/2003-03/msg00118.html */
#if LWIP_TCP
  struct tcp_pcb *pcb;
  struct tcp_pcb_listen *lpcb;

  /* address is actually being changed? */
  if (ipaddr && (ip_addr_cmp(ipaddr, &(netif->ip_addr))) == 0) {
    /* extern struct tcp_pcb *tcp_active_pcbs; defined by tcp.h */
    LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_STATE, ("netif_set_ipaddr: netif address being changed\n"));
    pcb = tcp_active_pcbs;
    while (pcb != NULL) {
      /* PCB bound to current local interface address? */
      if (ip_addr_cmp(&(pcb->local_ip), &(netif->ip_addr))
#if LWIP_AUTOIP
        /* connections to link-local addresses must persist (RFC3927 ch. 1.9) */
        && !ip_addr_islinklocal(&(pcb->local_ip))
#endif /* LWIP_AUTOIP */
        ) {
        /* this connection must be aborted */
        struct tcp_pcb *next = pcb->next;
        LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_STATE, ("netif_set_ipaddr: aborting TCP pcb %p\n", (void *)pcb));
        tcp_abort(pcb);
        pcb = next;
      } else {
        pcb = pcb->next;
      }
    }
    for (lpcb = tcp_listen_pcbs.listen_pcbs; lpcb != NULL; lpcb = lpcb->next) {
      /* PCB bound to current local interface address? */
      if ((!(ip_addr_isany(&(lpcb->local_ip)))) &&
          (ip_addr_cmp(&(lpcb->local_ip), &(netif->ip_addr)))) {
        /* The PCB is listening to the old ipaddr and
         * is set to listen to the new one instead */
        ip_addr_set(&(lpcb->local_ip), ipaddr);
      }
    }
  }
#endif /*LWIP_TCP*/
  snmp_delete_ipaddridx_tree(netif);
  snmp_delete_iprteidx_tree(0,netif);
  /* set new IP address to netif */
  ip_addr_set(&(netif->ip_addr), ipaddr);
  snmp_insert_ipaddridx_tree(netif);
  snmp_insert_iprteidx_tree(0,netif);

  LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE, ("netif: IP address of interface %c%c set to %"U16_F".%"U16_F".%"U16_F".%"U16_F"\n",
    netif->name[0], netif->name[1],
    ip4_addr1_16(&netif->ip_addr),
    ip4_addr2_16(&netif->ip_addr),
    ip4_addr3_16(&netif->ip_addr),
    ip4_addr4_16(&netif->ip_addr)));
}


/**
 * Set the netmask of a network interface.
 *
 * @param netif The network interface to set the netmask for.
 * @param netmask The new netmask to set.
 *
 * @note This function sets the netmask of the given network interface to the specified netmask.
 *       It performs the following actions:
 *       - Deletes and re-inserts the IP route index tree in the SNMP subsystem.
 *       - Sets the new netmask for the network interface.
 *       - Prints a debug message indicating the new netmask.
 *
 * @see ip_addr_t
 */
void
netif_set_netmask(struct netif *netif, ip_addr_t *netmask)
{
  snmp_delete_iprteidx_tree(0, netif);
  /* set new netmask to netif */
  ip_addr_set(&(netif->netmask), netmask);
  snmp_insert_iprteidx_tree(0, netif);
  LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE, ("netif: netmask of interface %c%c set to %"U16_F".%"U16_F".%"U16_F".%"U16_F"\n",
    netif->name[0], netif->name[1],
    ip4_addr1_16(&netif->netmask),
    ip4_addr2_16(&netif->netmask),
    ip4_addr3_16(&netif->netmask),
    ip4_addr4_16(&netif->netmask)));
}