#ifndef __ALINIX_KERNEL_NET_IP_H_INCLUDED
#define __ALINIX_KERNEL_NET_IP_H_INCLUDED

#include <alinix/types.h>
#include <net/ip_addr.h>

#define IP_PCB \
  /* ip addresses in network byte order */ \
  ip_addr_t local_ip; \
  ip_addr_t remote_ip; \
   /* Socket options */  \
  uint8_t so_options;      \
   /* Type Of Service */ \
  uint8_t tos;              \
  /* Time To Live */     \
  uint8_t ttl               \
  /* link layer address resolution hint */ \
//   IP_PCB_ADDRHINT

struct ip_pcb {
/* Common members of all PCB types */
  IP_PCB ;
};


#endif // __ALINIX_KERNEL_NET_IP_H_INCLUDED