#include <alinix/types.h>
#include <net/err.h>
#include <alinix/ip.h>
#include <net/udp.h>
#include <net/opt.h>
#include <alinix/memory.h>
#include <net/netif.h>

void netif_set_gw(struct netif *netif, ip_addr_t *gw);

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