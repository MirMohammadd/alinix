#include <net/err.h>
#include <alinix/types.h>
#include <net/ip_addr.h>
#include <net/etharp.h>
#include <net/debug.h>
#include <net/pbuf.h>
#include <net/stats.h>
#include <net/netif.h>
#include <net/opt.h>


#define ARP_MAXPENDING 2

#define HWTYPE_ETHERNET 1



const struct eth_addr ethbroadcast = {{0xff,0xff,0xff,0xff,0xff,0xff}};
const struct eth_addr ethzero = {{0,0,0,0,0,0}};


enum etharp_state {
  ETHARP_STATE_EMPTY = 0,
  ETHARP_STATE_PENDING,
  ETHARP_STATE_STABLE,
  ETHARP_STATE_STABLE_REREQUESTING
#if ETHARP_SUPPORT_STATIC_ENTRIES
  ,ETHARP_STATE_STATIC
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */
};
/** Clean up ARP table entries */
static void
etharp_free_entry(int i)
{
  /* remove from SNMP ARP index tree */
  snmp_delete_arpidx_tree(arp_table[i].netif, &arp_table[i].ipaddr);
  /* and empty packet queue */
  if (arp_table[i].q != NULL) {
    /* remove all queued packets */
    LWIP_DEBUGF(ETHARP_DEBUG, ("etharp_free_entry: freeing entry %"U16_F", packet queue %p.\n", (u16_t)i, (void *)(arp_table[i].q)));
    free_etharp_q(arp_table[i].q);
    arp_table[i].q = NULL;
  }
  /* recycle entry for re-use */
  arp_table[i].state = ETHARP_STATE_EMPTY;
#ifdef LWIP_DEBUG
  /* for debugging, clean out the complete entry */
  arp_table[i].ctime = 0;
  arp_table[i].netif = NULL;
  ip_addr_set_zero(&arp_table[i].ipaddr);
  arp_table[i].ethaddr = ethzero;
#endif /* LWIP_DEBUG */
}




struct etharp_entry {
#if ARP_QUEUEING
  /** Pointer to queue of pending outgoing packets on this ARP entry. */
  struct etharp_q_entry *q;
#else /* ARP_QUEUEING */
  /** Pointer to a single pending outgoing packet on this ARP entry. */
  struct pbuf *q;
#endif /* ARP_QUEUEING */
  ip_addr_t ipaddr;
  struct netif *netif;
  struct eth_addr ethaddr;
  uint8_t state;
  uint8_t ctime;
};

static struct etharp_entry arp_table[ARP_TABLE_SIZE];




void etharp_cleanup_netif(struct netif *netif)
{
  uint8_t i;

  for (i = 0; i < ARP_TABLE_SIZE; ++i) {
    uint8_t state = arp_table[i].state;
    if ((state != ETHARP_STATE_EMPTY) && (arp_table[i].netif == netif)) {
      etharp_free_entry(i);
    }
  }
}


err_t
etharp_raw(struct netif *netif, const struct eth_addr *ethsrc_addr,
           const struct eth_addr *ethdst_addr,
           const struct eth_addr *hwsrc_addr, const ip_addr_t *ipsrc_addr,
           const struct eth_addr *hwdst_addr, const ip_addr_t *ipdst_addr,
           const uint16_t opcode)
{
  struct pbuf *p;
  err_t result = ERR_OK;
  struct eth_hdr *ethhdr;
  struct etharp_hdr *hdr;
#if LWIP_AUTOIP
  const uint8_t * ethdst_hwaddr;
#endif /* LWIP_AUTOIP */

  LWIP_ASSERT("netif != NULL", netif != NULL);

  /* allocate a pbuf for the outgoing ARP request packet */
  p = pbuf_alloc(PBUF_RAW, SIZEOF_ETHARP_PACKET, PBUF_RAM);
  /* could allocate a pbuf for an ARP request? */
  if (p == NULL) {
    LWIP_DEBUGF(ETHARP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS,
      ("etharp_raw: could not allocate pbuf for ARP request.\n"));
    ETHARP_STATS_INC(etharp.memerr);
    return ERR_MEM;
  }
  LWIP_ASSERT("check that first pbuf can hold struct etharp_hdr",
              (p->len >= SIZEOF_ETHARP_PACKET));

  ethhdr = (struct eth_hdr *)p->payload;
  hdr = (struct etharp_hdr *)((uint8_t*)ethhdr + SIZEOF_ETH_HDR);
  LWIP_DEBUGF(ETHARP_DEBUG | LWIP_DBG_TRACE, ("etharp_raw: sending raw ARP packet.\n"));
  hdr->opcode = htons(opcode);

  LWIP_ASSERT("netif->hwaddr_len must be the same as ETHARP_HWADDR_LEN for etharp!",
              (netif->hwaddr_len == ETHARP_HWADDR_LEN));
#if LWIP_AUTOIP
  /* If we are using Link-Local, all ARP packets that contain a Link-Local
   * 'sender IP address' MUST be sent using link-layer broadcast instead of
   * link-layer unicast. (See RFC3927 Section 2.5, last paragraph) */
  ethdst_hwaddr = ip_addr_islinklocal(ipsrc_addr) ? (uint8_t*)(ethbroadcast.addr) : ethdst_addr->addr;
#endif /* LWIP_AUTOIP */
  /* Write the ARP MAC-Addresses */
  ETHADDR16_COPY(&hdr->shwaddr, hwsrc_addr);
  ETHADDR16_COPY(&hdr->dhwaddr, hwdst_addr);
  /* Write the Ethernet MAC-Addresses */
#if LWIP_AUTOIP
  ETHADDR16_COPY(&ethhdr->dest, ethdst_hwaddr);
#else  /* LWIP_AUTOIP */
  ETHADDR16_COPY(&ethhdr->dest, ethdst_addr);
#endif /* LWIP_AUTOIP */
  ETHADDR16_COPY(&ethhdr->src, ethsrc_addr);
  /* Copy struct ip_addr2 to aligned ip_addr, to support compilers without
   * structure packing. */ 
  IPADDR2_COPY(&hdr->sipaddr, ipsrc_addr);
  IPADDR2_COPY(&hdr->dipaddr, ipdst_addr);

  hdr->hwtype = PP_HTONS(HWTYPE_ETHERNET);
  hdr->proto = PP_HTONS(ETHTYPE_IP);
  /* set hwlen and protolen */
  hdr->hwlen = ETHARP_HWADDR_LEN;
  hdr->protolen = sizeof(ip_addr_t);

  ethhdr->type = PP_HTONS(ETHTYPE_ARP);
  /* send ARP query */
  result = netif->linkoutput(netif, p);
  ETHARP_STATS_INC(etharp.xmit);
  /* free ARP query packet */
  pbuf_free(p);
  p = NULL;
  /* could not allocate pbuf for ARP request */

  return result;
}