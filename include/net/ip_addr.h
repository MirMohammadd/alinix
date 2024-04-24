#ifndef __ALINIX_KERNEL_IP_ADDR_NET_H
#define __ALINIX_KERNEL_IP_ADDR_NET_H


#include <alinix/types.h>
#include <alinix/compiler.h>




struct ip_addr {
  uint32_t addr;
};

#define IP_ADDR_ANY         ((ip_addr_t *)&ip_addr_any)
#define IP_ADDR_BROADCAST   ((ip_addr_t *)&ip_addr_broadcast)
extern const ip_addr_t ip_addr_any;
extern const ip_addr_t ip_addr_broadcast;

typedef struct ip_addr ip_addr_t;

#endif /*__ALINIX_KERNEL_IP_ADDR_NET_H*/