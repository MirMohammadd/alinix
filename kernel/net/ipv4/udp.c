#include <alinix/types.h>
#include <net/err.h>
#include <alinix/ip.h>

err_t
udp_sendto_if(struct udp_pcb *pcb, struct pbuf *p,
  ip_addr_t *dst_ip, uint16_t dst_port, struct netif *netif)
{
// #if LWIP_CHECKSUM_ON_COPY
//   return udp_sendto_if_chksum(pcb, p, dst_ip, dst_port, netif, 0, 0);
}