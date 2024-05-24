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
 *  - Implements auto ip for the kernel drivers.
 * @todo:
 *  - Implement for C++.
*/


#include <alinix/types.h>
#include <alinix/compiler.h>
#include <net/ip.h>
#include <net/udp.h>
#include <net/netif.h>
#include <net/auto_ip.h>
#include <net/opt.h>
#include <net/arp.h>
#include <net/ip_addr.h>
#include <net/etharp.h>
#include <alinix/memory.h>
#include <net/err.h>
#include <net/def.h>
#include <net/inet.h>
#include <alinix/stdarg.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Auto IP for AliNix")
MODULE_LICENSE("AGPLv3")



/* 169.254.0.0 */
#define AUTOIP_NET         0xA9FE0000
/* 169.254.1.0 */
#define AUTOIP_RANGE_START (AUTOIP_NET | 0x0100)
/* 169.254.254.255 */
#define AUTOIP_RANGE_END   (AUTOIP_NET | 0xFEFF)


/** Pseudo random macro based on netif informations.
 * You could use "rand()" from the C Library if you define LWIP_AUTOIP_RAND in lwipopts.h */
#ifndef LWIP_AUTOIP_RAND
#define LWIP_AUTOIP_RAND(netif) ( (((uint32_t)((netif->hwaddr[5]) & 0xff) << 24) | \
                                   ((uint32_t)((netif->hwaddr[3]) & 0xff) << 16) | \
                                   ((uint32_t)((netif->hwaddr[2]) & 0xff) << 8) | \
                                   ((uint32_t)((netif->hwaddr[4]) & 0xff))) + \
                                   (netif->autoip?netif->autoip->tried_llipaddr:0))
#endif /* LWIP_AUTOIP_RAND */



#ifndef LWIP_AUTOIP_CREATE_SEED_ADDR
#define LWIP_AUTOIP_CREATE_SEED_ADDR(netif) \
  htonl(AUTOIP_RANGE_START + ((uint32_t)(((uint8_t)(netif->hwaddr[4])) | \
                 ((uint32_t)((uint8_t)(netif->hwaddr[5]))) << 8)))
#endif /* LWIP_AUTOIP_CREATE_SEED_ADDR */




/* static functions */
static void autoip_handle_arp_conflict(struct netif *netif);

/* creates a pseudo random LL IP-Address for a network interface */
static void autoip_create_addr(struct netif *netif, ip_addr_t *ipaddr);

/* sends an ARP probe */
static err_t autoip_arp_probe(struct netif *netif);

/* sends an ARP announce */
static err_t autoip_arp_announce(struct netif *netif);

/* configure interface for use with current LL IP-Address */
static err_t autoip_bind(struct netif *netif);

/* start sending probes for llipaddr */
static void autoip_start_probing(struct netif *netif);
static err_t
autoip_arp_announce(struct netif *netif)
{
  return etharp_raw(netif, (struct eth_addr *)netif->hwaddr, &ethbroadcast,
    (struct eth_addr *)netif->hwaddr, &netif->autoip->llipaddr, &ethzero,
    &netif->autoip->llipaddr, ARP_REQUEST);
}




static void
autoip_start_probing(struct netif *netif)
{
  struct autoip *autoip = netif->autoip;

  autoip->state = AUTOIP_STATE_PROBING;
  autoip->sent_num = 0;
  LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
     ("autoip_start_probing(): changing state to PROBING: %"U16_F".%"U16_F".%"U16_F".%"U16_F"\n",
      ip4_addr1_16(&netif->autoip->llipaddr), ip4_addr2_16(&netif->autoip->llipaddr),
      ip4_addr3_16(&netif->autoip->llipaddr), ip4_addr4_16(&netif->autoip->llipaddr)));

  /* time to wait to first probe, this is randomly
   * choosen out of 0 to PROBE_WAIT seconds.
   * compliant to RFC 3927 Section 2.2.1
   */
  autoip->ttw = (uint16_t)(LWIP_AUTOIP_RAND(netif) % (PROBE_WAIT * AUTOIP_TICKS_PER_SECOND));

  /*
   * if we tried more then MAX_CONFLICTS we must limit our rate for
   * accquiring and probing address
   * compliant to RFC 3927 Section 2.2.1
   */
  if (autoip->tried_llipaddr > MAX_CONFLICTS) {
    autoip->ttw = RATE_LIMIT_INTERVAL * AUTOIP_TICKS_PER_SECOND;
  }
}

err_t 
__autoip_start(struct netif *netif){
  struct autoip *autoip = netif->autoip;
  err_t result = ERR_OK;

  if (netif_is_up(netif)) {
    netif_set_down(netif);
  }

  /* Set IP-Address, Netmask and Gateway to 0 to make sure that
   * ARP Packets are formed correctly
   */
  ip_addr_set_zero(&netif->ip_addr);
  ip_addr_set_zero(&netif->netmask);
  ip_addr_set_zero(&netif->gw);

  LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
    ("autoip_start(netif=%p) %c%c%"U16_F"\n", (void*)netif, netif->name[0],
    netif->name[1], (uint16_t)netif->num));
  if (autoip == NULL) {
    /* no AutoIP client attached yet? */
    LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE,
      ("autoip_start(): starting new AUTOIP client\n"));
    autoip = (struct autoip *)mem_malloc(sizeof(struct autoip));
    if (autoip == NULL) {
      LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE,
        ("autoip_start(): could not allocate autoip\n"));
      return ERR_MEM;
    }
    memset(autoip, 0, sizeof(struct autoip));
    /* store this AutoIP client in the netif */
    netif->autoip = autoip;
    LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE, ("autoip_start(): allocated autoip"));
  } else {
    autoip->state = AUTOIP_STATE_OFF;
    autoip->ttw = 0;
    autoip->sent_num = 0;
    ip_addr_set_zero(&autoip->llipaddr);
    autoip->lastconflict = 0;
  }

  autoip_create_addr(netif, &(autoip->llipaddr));
  autoip_start_probing(netif);

  return result;
}


void
autoip_set_struct(struct netif *netif, struct autoip *autoip)
{
//   LWIP_ASSERT("netif != NULL", netif != NULL);
//   LWIP_ASSERT("autoip != NULL", autoip != NULL);
//   LWIP_ASSERT("netif already has a struct autoip set", netif->autoip == NULL);

  /* clear data structure */
  memset(autoip, 0, sizeof(struct autoip));
  /* autoip->state = AUTOIP_STATE_OFF; */
  netif->autoip = autoip;
}

PRIVATE VOID
autoip_restart(struct netif *netif)
{
  netif->autoip->tried_llipaddr++;
  __autoip_start(netif);
}


PRIVATE VOID
autoip_handle_arp_conflict(struct netif *netif)
{
  /* Somehow detect if we are defending or retreating */
  unsigned char defend = 1; /* tbd */

  if (defend) {
    if (netif->autoip->lastconflict > 0) {
      /* retreat, there was a conflicting ARP in the last
       * DEFEND_INTERVAL seconds
       */
      LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
        ("autoip_handle_arp_conflict(): we are defending, but in DEFEND_INTERVAL, retreating\n"));

      /* TODO: close all TCP sessions */
      autoip_restart(netif);
    } else {
      LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
        ("autoip_handle_arp_conflict(): we are defend, send ARP Announce\n"));
      autoip_arp_announce(netif);
      netif->autoip->lastconflict = DEFEND_INTERVAL * AUTOIP_TICKS_PER_SECOND;
    }
  } else {
    LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
      ("autoip_handle_arp_conflict(): we do not defend, retreating\n"));
    /* TODO: close all TCP sessions */
    autoip_restart(netif);
  }
}

static void
autoip_create_addr(struct netif *netif, ip_addr_t *ipaddr)
{
  /* Here we create an IP-Address out of range 169.254.1.0 to 169.254.254.255
   * compliant to RFC 3927 Section 2.1
   * We have 254 * 256 possibilities */

  uint32_t addr = ntohl(LWIP_AUTOIP_CREATE_SEED_ADDR(netif));
  addr += netif->autoip->tried_llipaddr;
  addr = AUTOIP_NET | (addr & 0xffff);
  /* Now, 169.254.0.0 <= addr <= 169.254.255.255 */ 

  if (addr < AUTOIP_RANGE_START) {
    addr += AUTOIP_RANGE_END - AUTOIP_RANGE_START + 1;
  }
  if (addr > AUTOIP_RANGE_END) {
    addr -= AUTOIP_RANGE_END - AUTOIP_RANGE_START + 1;
  }
  LWIP_ASSERT("AUTOIP address not in range", (addr >= AUTOIP_RANGE_START) &&
    (addr <= AUTOIP_RANGE_END));
  ip4_addr_set_u32(ipaddr, htonl(addr));
  
  LWIP_DEBUGF(AUTOIP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_STATE,
    ("autoip_create_addr(): tried_llipaddr=%"U16_F", %"U16_F".%"U16_F".%"U16_F".%"U16_F"\n",
    (uint16_t)(netif->autoip->tried_llipaddr), ip4_addr1_16(ipaddr), ip4_addr2_16(ipaddr),
    ip4_addr3_16(ipaddr), ip4_addr4_16(ipaddr)));
}

static err_t
autoip_arp_probe(struct netif *netif)
{
  return etharp_raw(netif, (struct eth_addr *)netif->hwaddr, &ethbroadcast,
    (struct eth_addr *)netif->hwaddr, IP_ADDR_ANY, &ethzero,
    &netif->autoip->llipaddr, ARP_REQUEST);
}