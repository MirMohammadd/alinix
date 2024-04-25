#include <alinix/types.h>
#include <net/err.h>
#include <alinix/ip.h>
#include <net/udp.h>
#include <net/opt.h>

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