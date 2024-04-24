#ifndef __ALINIX_KERNEL_ETH_ARP_H_NET
#define __ALINIX_KERNEL_ETH_ARP_H_NET

#include <alinix/compiler.h>
#include <alinix/types.h>
#include <net/ip_addr.h>
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


PACK_STRUCT_BEGIN
/** the ARP message, see RFC 826 ("Packet format") */
struct etharp_hdr {
  PACK_STRUCT_FIELD(uint16_t hwtype);
  PACK_STRUCT_FIELD(uint16_t proto);
  PACK_STRUCT_FIELD(uint8_t  hwlen);
  PACK_STRUCT_FIELD(uint8_t  protolen);
  PACK_STRUCT_FIELD(uint16_t opcode);
  PACK_STRUCT_FIELD(struct eth_addr shwaddr);
  PACK_STRUCT_FIELD(struct ip_addr2 sipaddr);
  PACK_STRUCT_FIELD(struct eth_addr dhwaddr);
  PACK_STRUCT_FIELD(struct ip_addr2 dipaddr);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

struct eth_hdr {
#if ETH_PAD_SIZE
  PACK_STRUCT_FIELD(uint8_t padding[ETH_PAD_SIZE]);
#endif
  PACK_STRUCT_FIELD(struct eth_addr dest);
  PACK_STRUCT_FIELD(struct eth_addr src);
  PACK_STRUCT_FIELD(uint16_t type);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

#endif // __ALINIX_KERNEL_ETH_ARP_H_NET