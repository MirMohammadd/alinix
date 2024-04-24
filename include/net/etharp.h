#ifndef __ALINIX_KERNEL_ETH_ARP_H_NET
#define __ALINIX_KERNEL_ETH_ARP_H_NET

#include <alinix/compiler.h>
#include <alinix/types.h>
#ifndef ETHARP_HWADDR_LEN
#define ETHARP_HWADDR_LEN     6
#endif

extern const struct eth_addr ethbroadcast, ethzero;


PACK_STRUCT_BEGIN
struct eth_addr {
  PACK_STRUCT_FIELD(uint8_t addr[ETHARP_HWADDR_LEN]);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

#endif // __ALINIX_KERNEL_ETH_ARP_H_NET