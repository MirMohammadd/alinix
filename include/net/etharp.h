#ifndef __ALINIX_KERNEL_ETH_ARP_H_NET
#define __ALINIX_KERNEL_ETH_ARP_H_NET

#include <alinix/compiler.h>
#include <alinix/types.h>
#ifndef ETHARP_HWADDR_LEN
#define ETHARP_HWADDR_LEN     6
#endif


#define ETHTYPE_ARP       0x0806U
#define ETHTYPE_IP        0x0800U
#define ETHTYPE_VLAN      0x8100U
#define ETHTYPE_PPPOEDISC 0x8863U  /* PPP Over Ethernet Discovery Stage */
#define ETHTYPE_PPPOE     0x8864U  /* PPP Over Ethernet Session Stage */

#define SIZEOF_ETHARP_HDR 28
#define SIZEOF_ETHARP_PACKET (SIZEOF_ETH_HDR + SIZEOF_ETHARP_HDR)

extern const struct eth_addr ethbroadcast, ethzero;


PACK_STRUCT_BEGIN
struct eth_addr {
  PACK_STRUCT_FIELD(uint8_t addr[ETHARP_HWADDR_LEN]);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

#endif // __ALINIX_KERNEL_ETH_ARP_H_NET