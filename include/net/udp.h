#ifndef __ALINIX_KERNEL_NET_UDP_H
#define __ALINIX_KERNEL_NET_UDP_H

#include <alinix/types.h>
#include <alinix/compiler.h>
#include <net/ip_addr.h>
#include <net/ip.h>


#ifdef __cplusplus
extern "C"{
#endif


#define UPD_HELEN 8
struct udp_hdr {
  PACK_STRUCT_FIELD(uint16_t src);
  PACK_STRUCT_FIELD(uint16_t dest);  /* src/dest UDP ports */
  PACK_STRUCT_FIELD(uint16_t len);
  PACK_STRUCT_FIELD(uint16_t chksum);
} PACK_STRUCT_STRUCT;


#define UDP_FLAGS_NOCHKSUM       0x01U
#define UDP_FLAGS_UDPLITE        0x02U
#define UDP_FLAGS_CONNECTED      0x04U
#define UDP_FLAGS_MULTICAST_LOOP 0x08U

struct udp_pcb;


typedef void (*udp_recv_fn)(void *arg, struct udp_pcb *pcb, struct pbuf *p,
    ip_addr_t *addr, uint16_t port);


struct udp_pcb {
/* Common members of all PCB types */
  IP_PCB;

/* Protocol specific PCB members */

  struct udp_pcb *next;

  uint8_t flags;
  /** ports are in host byte order */
  uint16_t local_port, remote_port;

#if LWIP_IGMP
  /** outgoing network interface for multicast packets */
  ip_addr_t multicast_ip;
#endif /* LWIP_IGMP */

#if LWIP_UDPLITE
  /** used for UDP_LITE only */
  uint16_t chksum_len_rx, chksum_len_tx;
#endif /* LWIP_UDPLITE */

  /** receive callback function */
  udp_recv_fn recv;
  /** user-supplied argument for the recv callback */
  void *recv_arg;  
};

#ifdef __cplusplus
}
#endif

#endif /*__ALINIX_KERNEL_NET_UDP_H*/