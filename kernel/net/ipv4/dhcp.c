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

#include <alinix/compiler.h>
#include <alinix/types.h>
#include <alinix/memory.h>
#include <alinix/ip.h>
#include <alinix/if_arp.h>

#include <net/dhcp.h>
#include <net/debug.h>


/** DHCP_OPTION_MAX_MSG_SIZE is set to the MTU
 * MTU is checked to be big enough in dhcp_start */
#define DHCP_MAX_MSG_LEN(netif)        (netif->mtu)
#define DHCP_MAX_MSG_LEN_MIN_REQUIRED  576
/** Minimum length for reply before packet is parsed */
#define DHCP_MIN_REPLY_LEN             44

#define REBOOT_TRIES 2

/** Option handling: options are parsed in dhcp_parse_reply
 * and saved in an array where other functions can load them from.
 * This might be moved into the struct dhcp (not necessarily since
 * lwIP is single-threaded and the array is only used while in recv
 * callback). */
#define DHCP_OPTION_IDX_OVERLOAD    0
#define DHCP_OPTION_IDX_MSG_TYPE    1
#define DHCP_OPTION_IDX_SERVER_ID   2
#define DHCP_OPTION_IDX_LEASE_TIME  3
#define DHCP_OPTION_IDX_T1          4
#define DHCP_OPTION_IDX_T2          5
#define DHCP_OPTION_IDX_SUBNET_MASK 6
#define DHCP_OPTION_IDX_ROUTER      7
#define DHCP_OPTION_IDX_DNS_SERVER  8
#define DHCP_OPTION_IDX_MAX         (DHCP_OPTION_IDX_DNS_SERVER + DNS_MAX_SERVERS)

/** Holds the decoded option values, only valid while in dhcp_recv.
    @todo: move this into struct dhcp? */
uint32_t dhcp_rx_options_val[DHCP_OPTION_IDX_MAX];
/** Holds a flag which option was received and is contained in dhcp_rx_options_val,
    only valid while in dhcp_recv.
    @todo: move this into struct dhcp? */
uint8_t  dhcp_rx_options_given[DHCP_OPTION_IDX_MAX];

static uint32_t xid;
static uint8_t xid_initialised;

#define dhcp_option_given(dhcp, idx)          (dhcp_rx_options_given[idx] != 0)
#define dhcp_got_option(dhcp, idx)            (dhcp_rx_options_given[idx] = 1)
#define dhcp_clear_option(dhcp, idx)          (dhcp_rx_options_given[idx] = 0)
#define dhcp_clear_all_options(dhcp)          (memset(dhcp_rx_options_given, 0, sizeof(dhcp_rx_options_given)))
#define dhcp_get_option_value(dhcp, idx)      (dhcp_rx_options_val[idx])
#define dhcp_set_option_value(dhcp, idx, val) (dhcp_rx_options_val[idx] = (val))


/* DHCP client state machine functions */
static err_t dhcp_discover(struct netif *netif);
static err_t dhcp_select(struct netif *netif);
static void dhcp_bind(struct netif *netif);
#if DHCP_DOES_ARP_CHECK
static err_t dhcp_decline(struct netif *netif);
#endif /* DHCP_DOES_ARP_CHECK */
static err_t dhcp_rebind(struct netif *netif);
static err_t dhcp_reboot(struct netif *netif);
static void dhcp_set_state(struct dhcp *dhcp, uint8_t new_state);

/* receive, unfold, parse and free incoming messages */
static void dhcp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *addr, uint16_t port);

/* set the DHCP timers */
static void dhcp_timeout(struct netif *netif);
static void dhcp_t1_timeout(struct netif *netif);
static void dhcp_t2_timeout(struct netif *netif);

/* build outgoing messages */
/* create a DHCP message, fill in common headers */
static err_t dhcp_create_msg(struct netif *netif, struct dhcp *dhcp, uint8_t message_type);
/* free a DHCP request */
static void dhcp_delete_msg(struct dhcp *dhcp);
/* add a DHCP option (type, then length in bytes) */
static void dhcp_option(struct dhcp *dhcp, uint8_t option_type, uint8_t option_len);
/* add option values */
static void dhcp_option_byte(struct dhcp *dhcp, uint8_t value);
static void dhcp_option_short(struct dhcp *dhcp, uint16_t value);
static void dhcp_option_long(struct dhcp *dhcp, uint32_t value);
#if LWIP_NETIF_HOSTNAME
static void dhcp_option_hostname(struct dhcp *dhcp, struct netif *netif);
#endif /* LWIP_NETIF_HOSTNAME */
/* always add the DHCP options trailer to end and pad */
static void dhcp_option_trailer(struct dhcp *dhcp);


static void
dhcp_handle_nak(struct netif *netif)
{
  struct dhcp *dhcp = netif->dhcp;
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_handle_nak(netif=%p) %c%c%"U16_F"\n", 
    (void*)netif, netif->name[0], netif->name[1], (uint16_t)netif->num));
  /* Set the interface down since the address must no longer be used, as per RFC2131 */
  netif_set_down(netif);
  /* remove IP address from interface */
  netif_set_ipaddr(netif, IP_ADDR_ANY);
  netif_set_gw(netif, IP_ADDR_ANY);
  netif_set_netmask(netif, IP_ADDR_ANY); 
  /* Change to a defined state */
  dhcp_set_state(dhcp, DHCP_BACKING_OFF);
  /* We can immediately restart discovery */
  dhcp_discover(netif);
}


static void
dhcp_check(struct netif *netif)
{
  struct dhcp *dhcp = netif->dhcp;
  err_t result;
  uint16_t msecs;
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_check(netif=%p) %c%c\n", (void *)netif, (s16_t)netif->name[0],
    (s16_t)netif->name[1]));
  dhcp_set_state(dhcp, DHCP_CHECKING);
  /* create an ARP query for the offered IP address, expecting that no host
     responds, as the IP address should not be in use. */
  result = etharp_query(netif, &dhcp->offered_ip_addr, NULL);
  if (result != ERR_OK) {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING, ("dhcp_check: could not perform ARP query\n"));
  }
  dhcp->tries++;
  msecs = 500;
  dhcp->request_timeout = (msecs + DHCP_FINE_TIMER_MSECS - 1) / DHCP_FINE_TIMER_MSECS;
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE, ("dhcp_check(): set request timeout %"U16_F" msecs\n", msecs));
}

static void
dhcp_handle_offer(struct netif *netif)
{
  struct dhcp *dhcp = netif->dhcp;
  LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_handle_offer(netif=%p) %c%c%"U16_F"\n",
    (void*)netif, netif->name[0], netif->name[1], (uint16_t)netif->num));
  /* obtain the server address */
  if (dhcp_option_given(dhcp, DHCP_OPTION_IDX_SERVER_ID)) {
    ip4_addr_set_u32(&dhcp->server_ip_addr, htonl(dhcp_get_option_value(dhcp, DHCP_OPTION_IDX_SERVER_ID)));
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_STATE, ("dhcp_handle_offer(): server 0x%08"X32_F"\n",
      ip4_addr_get_u32(&dhcp->server_ip_addr)));
    /* remember offered address */
    ip_addr_copy(dhcp->offered_ip_addr, dhcp->msg_in->yiaddr);
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_STATE, ("dhcp_handle_offer(): offer for 0x%08"X32_F"\n",
      ip4_addr_get_u32(&dhcp->offered_ip_addr)));

    dhcp_select(netif);
  } else {
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS,
      ("dhcp_handle_offer(netif=%p) did not get server ID!\n", (void*)netif));
  }
}
