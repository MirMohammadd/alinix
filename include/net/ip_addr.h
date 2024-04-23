#ifndef __ALINIX_KERNEL_IP_ADDR_NET_H
#define __ALINIX_KERNEL_IP_ADDR_NET_H


#include <alinix/types.h>
#include <alinix/compiler.h>


struct ip_addr {
  uint32_t addr;
};

typedef struct ip_addr ip_addr_t;

#endif /*__ALINIX_KERNEL_IP_ADDR_NET_H*/