#ifndef __ALINIX_KERNEL_IP_ADDR_NET_H
#define __ALINIX_KERNEL_IP_ADDR_NET_H


#include <alinix/types.h>
#include <alinix/compiler.h>

// This should be defined on the top
typedef struct ip_addr ip_addr_t;


struct ip_addr {
  uint32_t addr;
};

#define IP_ADDR_ANY         ((ip_addr_t *)&ip_addr_any)
#define IP_ADDR_BROADCAST   ((ip_addr_t *)&ip_addr_broadcast)
extern const ip_addr_t ip_addr_any;
extern const ip_addr_t ip_addr_broadcast;


#endif /*__ALINIX_KERNEL_IP_ADDR_NET_H*/