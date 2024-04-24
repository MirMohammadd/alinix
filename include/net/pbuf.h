#ifndef __ALINIX_KERNEL_PBUF_HEADER_NET_INCLUDED_H
#define __ALINIX_KERNEL_PBUF_HEADER_NET_INCLUDED_H

#include <alinix/types.h>

typedef enum {
  PBUF_TRANSPORT,
  PBUF_IP,
  PBUF_LINK,
  PBUF_RAW
} pbuf_layer;


struct pbuf {
  /** next pbuf in singly linked pbuf chain */
  struct pbuf *next;

  /** pointer to the actual data in the buffer */
  void *payload;

  /**
   * total length of this buffer and all next buffers in chain
   * belonging to the same packet.
   *
   * For non-queue packet chains this is the invariant:
   * p->tot_len == p->len + (p->next? p->next->tot_len: 0)
   */
  uint16_t tot_len;

  /** length of this buffer */
  uint16_t len;

  /** pbuf_type as uint8_t instead of enum to save space */
  uint8_t /*pbuf_type*/ type;

  /** misc flags */
  uint8_t flags;

  /**
   * the reference count always equals the number of pointers
   * that refer to this pbuf. This can be pointers from an application,
   * the stack itself, or pbuf->next pointers from a chain.
   */
  uint16_t ref;
};

#endif	/* __ALINIX_KERNEL_PBUF_HEADER_NET_INCLUDED_H */