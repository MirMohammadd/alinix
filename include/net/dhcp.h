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
#ifndef __ALINIX_KERNEL_NET_DHCP_H
#define __ALINIX_KERNEL_NET_DHCP_H

#include <net/opt.h>
#include <net/udp.h>
#include <net/ip_addr.h>
#include <net/netif.h>

#include <alinix/types.h>
#include <alinix/compiler.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



//////////////////
// Define Useful macros fir DHCP


/** period (in seconds) of the application calling dhcp_coarse_tmr() */
#define DHCP_COARSE_TIMER_SECS 60 
/** period (in milliseconds) of the application calling dhcp_coarse_tmr() */
#define DHCP_COARSE_TIMER_MSECS (DHCP_COARSE_TIMER_SECS * 1000UL)
/** period (in milliseconds) of the application calling dhcp_fine_tmr() */
#define DHCP_FINE_TIMER_MSECS 500 

#define DHCP_CHADDR_LEN 16U
#define DHCP_SNAME_LEN  64U
#define DHCP_FILE_LEN   128U


struct dhcp{
    /** transaction identifier of last sent request */ 
    uint32_t xid;
    /** our connection to the DHCP server */ 
    struct udp_pcb *pcb;
    /** incoming msg */
    struct dhcp_msg *msg_in;
};


struct dhcp_msg
{
  PACK_STRUCT_FIELD(uint8_t op);
  PACK_STRUCT_FIELD(uint8_t htype);
  PACK_STRUCT_FIELD(uint8_t hlen);
  PACK_STRUCT_FIELD(uint8_t hops);
  PACK_STRUCT_FIELD(uint32_t xid);
  PACK_STRUCT_FIELD(uint16_t secs);
  PACK_STRUCT_FIELD(uint16_t flags);
  PACK_STRUCT_FIELD(ip_addr_p_t ciaddr);
  PACK_STRUCT_FIELD(ip_addr_p_t yiaddr);
  PACK_STRUCT_FIELD(ip_addr_p_t siaddr);
  PACK_STRUCT_FIELD(ip_addr_p_t giaddr);
  PACK_STRUCT_FIELD(uint8_t chaddr[DHCP_CHADDR_LEN]);
  PACK_STRUCT_FIELD(uint8_t sname[DHCP_SNAME_LEN]);
  PACK_STRUCT_FIELD(uint8_t file[DHCP_FILE_LEN]);
  PACK_STRUCT_FIELD(uint32_t cookie);
#define DHCP_MIN_OPTIONS_LEN 68U
/** make sure user does not configure this too small */
#if ((defined(DHCP_OPTIONS_LEN)) && (DHCP_OPTIONS_LEN < DHCP_MIN_OPTIONS_LEN))
#  undef DHCP_OPTIONS_LEN
#endif
/** allow this to be configured in lwipopts.h, but not too small */
#if (!defined(DHCP_OPTIONS_LEN))
/** set this to be sufficient for your options in outgoing DHCP msgs */
#  define DHCP_OPTIONS_LEN DHCP_MIN_OPTIONS_LEN
#endif
  PACK_STRUCT_FIELD(uint8_t options[DHCP_OPTIONS_LEN]);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END


void dhcp_set_struct(struct netif *netif, struct dhcp *dhcp);
#define dhcp_remove_struct(netif) do {(netif)->dhcp = NULL;} while (0)
void dhcp_cleanup(struct netif *netif);
/** start DHCP configuration */
err_t dhcp_start(struct netif *netif);
/** enforce early lease renewal (not needed normally)*/
err_t dhcp_renew(struct netif *netif);
/** release the DHCP lease, usually called before dhcp_stop()*/
err_t dhcp_release(struct netif *netif);
/** stop DHCP configuration */
void dhcp_stop(struct netif *netif);
/** inform server of our manual IP address */
void dhcp_inform(struct netif *netif);
/** Handle a possible change in the network configuration */
void dhcp_network_changed(struct netif *netif);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif