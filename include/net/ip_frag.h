#ifndef __ALINIX_KERNEL_NET_IP_FRAG_H
#define __ALINIX_KERNEL_NET_IP_FRAG_H

#include <net/pbuf.h>
#include <net/perf.h>


typedef void (*pbuf_free_custom_fn)(struct pbuf *p);

struct pbuf_custom {
  /** The actual pbuf */
  struct pbuf pbuf;
  /** This function is called when pbuf_free deallocates this pbuf(_custom) */
  pbuf_free_custom_fn custom_free_function;
};


struct pbuf_custom_ref {
  /** 'base class' */
  struct pbuf_custom pc;
  /** pointer to the original pbuf that is referenced */
  struct pbuf *original;
};
#endif /* !IP_FRAG_USES_STATIC_BUF && !LWIP_NETIF_TX_SINGLE_PBUF */
