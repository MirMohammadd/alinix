#ifndef __ALINIX_KERNEL_NET_TYPING_H
#define __ALINIX_KERNEL_NET_TYPING_H

#include <net/ip_addr.h>

typedef err_t (*netif_init_fn)(struct netif *netif);

typedef err_t (*netif_input_fn)(struct pbuf *p, struct netif *inp);

typedef err_t (*netif_output_fn)(struct netif *netif, struct pbuf *p,
       ip_addr_t *ipaddr);


typedef err_t (*netif_linkoutput_fn)(struct netif *netif, struct pbuf *p);
/** Function prototype for netif status- or link-callback functions. */


#endif // __ALINIX_KERNEL_NET_TYPING_H