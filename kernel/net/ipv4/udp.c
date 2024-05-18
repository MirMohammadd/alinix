/**
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
 * @abstract:
 *  Implements UDP connection for kernel.
*/
#include <alinix/types.h>
#include <net/err.h>
#include <alinix/ip.h>
#include <net/udp.h>
#include <net/opt.h>
#include <alinix/memory.h>
#include <net/netif.h>
#include <alinix/arch.h>

void netif_set_gw(struct netif *netif, ip_addr_t *gw);

struct udp_pcb *udp_pcbs;

err_t
udp_sendto_if(struct udp_pcb *pcb, struct pbuf *p,
  ip_addr_t *dst_ip, uint16_t dst_port, struct netif *netif);

err_t
udp_sendto_if(struct udp_pcb *pcb, struct pbuf *p,
  ip_addr_t *dst_ip, uint16_t dst_port, struct netif *netif)
{
// #if LWIP_CHECKSUM_ON_COPY
//   return udp_sendto_if_chksum(pcb, p, dst_ip, dst_port, netif, 0, 0);
}

void
udp_remove(struct udp_pcb *pcb)
{
  struct udp_pcb *pcb2;

  snmp_delete_udpidx_tree(pcb);
  /* pcb to be removed is first in list? */
  if (udp_pcbs == pcb) {
    /* make list start at 2nd pcb */
    udp_pcbs = udp_pcbs->next;
    /* pcb not 1st in list */
  } else {
    for (pcb2 = udp_pcbs; pcb2 != NULL; pcb2 = pcb2->next) {
      /* find pcb in udp_pcbs list */
      if (pcb2->next != NULL && pcb2->next == pcb) {
        /* remove pcb from list */
        pcb2->next = pcb->next;
      }
    }
  }
  memp_free(MEMP_DEBUG, pcb);
}


void
netif_set_gw(struct netif *netif, ip_addr_t *gw)
{
  ip_addr_set(&(netif->gw), gw);
  LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE, ("netif: GW address of interface %c%c set to %"U16_F".%"U16_F".%"U16_F".%"U16_F"\n",
    netif->name[0], netif->name[1],
    ip4_addr1_16(&netif->gw),
    ip4_addr2_16(&netif->gw),
    ip4_addr3_16(&netif->gw),
    ip4_addr4_16(&netif->gw)));
}

struct udp_pcb *
udp_new(void)
{
  struct udp_pcb *pcb;
  pcb = (struct udp_pcb *)memp_malloc(MEM_DEBUG);
  /* could allocate UDP PCB? */
  if (pcb != NULL) {
    /* UDP Lite: by initializing to all zeroes, chksum_len is set to 0
     * which means checksum is generated over the whole datagram per default
     * (recommended as default by RFC 3828). */
    /* initialize PCB to all zeroes */
    memset(pcb, 0, sizeof(struct udp_pcb));
  }
  return pcb;
}


err_t
udp_bind(struct udp_pcb *pcb, ip_addr_t *ipaddr, uint16_t port)
{
//   struct udp_pcb *ipcb;
//   uint8_t rebind;

//   LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE, ("udp_bind(ipaddr = "));
//   ip_addr_debug_print(UDP_DEBUG, ipaddr);
//   LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE, (", port = %"U16_F")\n", port));

//   rebind = 0;
//   /* Check for double bind and rebind of the same pcb */
//   for (ipcb = udp_pcbs; ipcb != NULL; ipcb = ipcb->next) {
//     /* is this UDP PCB already on active list? */
//     if (pcb == ipcb) {
//       /* pcb may occur at most once in active list */
//       LWIP_ASSERT("rebind == 0", rebind == 0);
//       /* pcb already in list, just rebind */
//       rebind = 1;
//     }

//     /* By default, we don't allow to bind to a port that any other udp
//        PCB is alread bound to, unless *all* PCBs with that port have tha
//        REUSEADDR flag set. */
// #if SO_REUSE
//     else if (!ip_get_option(pcb, SOF_REUSEADDR) &&
//              !ip_get_option(ipcb, SOF_REUSEADDR)) {
// #else /* SO_REUSE */
//     /* port matches that of PCB in list and REUSEADDR not set -> reject */
//     else {
// #endif /* SO_REUSE */
//       if ((ipcb->local_port == port) &&
//           /* IP address matches, or one is IP_ADDR_ANY? */
//           (ip_addr_isany(&(ipcb->local_ip)) ||
//            ip_addr_isany(ipaddr) ||
//            ip_addr_cmp(&(ipcb->local_ip), ipaddr))) {
//         /* other PCB already binds to this local IP and port */
//         LWIP_DEBUGF(UDP_DEBUG,
//                     ("udp_bind: local port %"U16_F" already bound by another pcb\n", port));
//         return ERR_USE;
//       }
//     }
//   }

//   ip_addr_set(&pcb->local_ip, ipaddr);

//   /* no port specified? */
//   if (port == 0) {
//     port = udp_new_port();
//     if (port == 0) {
//       /* no more ports available in local range */
//       LWIP_DEBUGF(UDP_DEBUG, ("udp_bind: out of free UDP ports\n"));
//       return ERR_USE;
//     }
//   }
//   pcb->local_port = port;
//   snmp_insert_udpidx_tree(pcb);
//   /* pcb not active yet? */
//   if (rebind == 0) {
//     /* place the PCB on the active list if not already there */
//     pcb->next = udp_pcbs;
//     udp_pcbs = pcb;
//   }
//   LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
//               ("udp_bind: bound to %"U16_F".%"U16_F".%"U16_F".%"U16_F", port %"U16_F"\n",
//                ip4_addr1_16(&pcb->local_ip), ip4_addr2_16(&pcb->local_ip),
//                ip4_addr3_16(&pcb->local_ip), ip4_addr4_16(&pcb->local_ip),
//                pcb->local_port));
//   return ERR_OK;
}

err_t
udp_connect(struct udp_pcb *pcb, ip_addr_t *ipaddr, uint16_t port)
{
  struct udp_pcb *ipcb;

  if (pcb->local_port == 0) {
    err_t err = udp_bind(pcb, &pcb->local_ip, pcb->local_port);
    if (err != ERR_OK) {
      return err;
    }
  }

  ip_addr_set(&pcb->remote_ip, ipaddr);
  pcb->remote_port = port;
  pcb->flags |= UDP_FLAGS_CONNECTED;
/** TODO: this functionality belongs in upper layers */
  LWIP_DEBUGF(UDP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
              ("udp_connect: connected to %"U16_F".%"U16_F".%"U16_F".%"U16_F",port %"U16_F"\n",
               ip4_addr1_16(&pcb->local_ip), ip4_addr2_16(&pcb->local_ip),
               ip4_addr3_16(&pcb->local_ip), ip4_addr4_16(&pcb->local_ip),
               pcb->local_port));

  /* Insert UDP PCB into the list of active UDP PCBs. */
  for (ipcb = udp_pcbs; ipcb != NULL; ipcb = ipcb->next) {
    if (pcb == ipcb) {
      /* already on the list, just return */
      return ERR_OK;
    }
  }
  /* PCB not yet on the list, add PCB now */
  pcb->next = udp_pcbs;
  udp_pcbs = pcb;
  return ERR_OK;
}


void
udp_recv(struct udp_pcb *pcb, udp_recv_fn recv, void *recv_arg)
{
  /* remember recv() callback and user data */
  pcb->recv = recv;
  pcb->recv_arg = recv_arg;
}