#ifndef __ALINIX_KERNEL_NET_TYPING_H
#define __ALINIX_KERNEL_NET_TYPING_H

#include <net/ip_addr.h>

struct ip_addr {
  uint32_t addr;
};

struct ip_addr_packed {
  PACK_STRUCT_FIELD(uint32_t addr);
} PACK_STRUCT_STRUCT;


// This should be defined on the top
typedef struct ip_addr ip_addr_t;
typedef struct ip_addr_packed ip_addr_p_t;

typedef err_t (*netif_init_fn)(struct netif *netif);

typedef err_t (*netif_input_fn)(struct pbuf *p, struct netif *inp);

typedef err_t (*netif_output_fn)(struct netif *netif, struct pbuf *p,
       ip_addr_t *ipaddr);


typedef err_t (*netif_linkoutput_fn)(struct netif *netif, struct pbuf *p);
/** Function prototype for netif status- or link-callback functions. */


#endif // __ALINIX_KERNEL_NET_TYPING_H