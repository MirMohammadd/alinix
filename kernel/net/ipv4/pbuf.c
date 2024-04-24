#include <net/pbuf.h>
#include <alinix/types.h>
#include <net/opt.h>
#include <net/debug.h>
#include <alinix/memory.h>
#include <alinix/compiler.h>
#include <net/mem.h>

#define PBUF_POOL_BUFSIZE_ALIGNED LWIP_MEM_ALIGN_SIZE(PBUF_POOL_BUFSIZE)
#define SIZEOF_STRUCT_PBUF        LWIP_MEM_ALIGN_SIZE(sizeof(struct pbuf))


#define PBUF_POOL_IS_EMPTY() pbuf_pool_is_empty()
volatile uint8_t pbuf_free_ooseq_pending;

static void
pbuf_pool_is_empty(void)
{
#ifndef PBUF_POOL_FREE_OOSEQ_QUEUE_CALL
  pbuf_free_ooseq_pending = 1;
#else /* PBUF_POOL_FREE_OOSEQ_QUEUE_CALL */
  uint8_t queued;
  SYS_ARCH_DECL_PROTECT(old_level);
  SYS_ARCH_PROTECT(old_level);
  queued = pbuf_free_ooseq_pending;
  pbuf_free_ooseq_pending = 1;
  SYS_ARCH_UNPROTECT(old_level);

  if(!queued) {
    /* queue a call to pbuf_free_ooseq if not already queued */
    PBUF_POOL_FREE_OOSEQ_QUEUE_CALL();
  }
#endif /* PBUF_POOL_FREE_OOSEQ_QUEUE_CALL */
}



struct pbuf *
pbuf_alloc(pbuf_layer layer, uint16_t length, pbuf_type type)
{
  struct pbuf *p, *q, *r;
  uint16_t offset;
  uint32_t rem_len; /* remaining length */
  LWIP_DEBUGF(PBUF_DEBUG | LWIP_DBG_TRACE, ("pbuf_alloc(length=%"U16_F")\n", length));

  /* determine header offset */
  switch (layer) {
  case PBUF_TRANSPORT:
    /* add room for transport (often TCP) layer header */
    offset = PBUF_LINK_HLEN + PBUF_IP_HLEN + PBUF_TRANSPORT_HLEN;
    break;
  case PBUF_IP:
    /* add room for IP layer header */
    offset = PBUF_LINK_HLEN + PBUF_IP_HLEN;
    break;
  case PBUF_LINK:
    /* add room for link layer header */
    offset = PBUF_LINK_HLEN;
    break;
  case PBUF_RAW:
    offset = 0;
    break;
  default:
    LWIP_ASSERT("pbuf_alloc: bad pbuf layer", 0);
    return NULL;
  }

  switch (type) {
  case PBUF_POOL:
    /* allocate head of pbuf chain into p */
    p = (struct pbuf *)memp_malloc(MEM_DEBUG);
    LWIP_DEBUGF(PBUF_DEBUG | LWIP_DBG_TRACE, ("pbuf_alloc: allocated pbuf %p\n", (void *)p));
    if (p == NULL) {
      PBUF_POOL_IS_EMPTY();
      return NULL;
    }
    p->type = type;
    p->next = NULL;

    /* make the payload pointer point 'offset' bytes into pbuf data memory */
    p->payload = LWIP_MEM_ALIGN((void *)((uint8_t *)p + (SIZEOF_STRUCT_PBUF + offset)));
    LWIP_ASSERT("pbuf_alloc: pbuf p->payload properly aligned",
            ((mem_ptr_t)p->payload % MEM_ALIGNMENT) == 0);
    /* the total length of the pbuf chain is the requested size */
    p->tot_len = length;
    /* set the length of the first pbuf in the chain */
    p->len = LWIP_MIN(length, PBUF_POOL_BUFSIZE_ALIGNED - LWIP_MEM_ALIGN_SIZE(offset));
    LWIP_ASSERT("check p->payload + p->len does not overflow pbuf",
                ((uint8_t*)p->payload + p->len <=
                 (uint8_t*)p + SIZEOF_STRUCT_PBUF + PBUF_POOL_BUFSIZE_ALIGNED));
    LWIP_ASSERT("PBUF_POOL_BUFSIZE must be bigger than MEM_ALIGNMENT",
      (PBUF_POOL_BUFSIZE_ALIGNED - LWIP_MEM_ALIGN_SIZE(offset)) > 0 );
    /* set reference count (needed here in case we fail) */
    p->ref = 1;

    /* now allocate the tail of the pbuf chain */

    /* remember first pbuf for linkage in next iteration */
    r = p;
    /* remaining length to be allocated */
    rem_len = length - p->len;
    /* any remaining pbufs to be allocated? */
    while (rem_len > 0) {
      q = (struct pbuf *)memp_malloc(MEMP_DEBUG);
      if (q == NULL) {
        PBUF_POOL_IS_EMPTY();
        /* free chain so far allocated */
        pbuf_free(p);
        /* bail out unsuccesfully */
        return NULL;
      }
      q->type = type;
      q->flags = 0;
      q->next = NULL;
      /* make previous pbuf point to this pbuf */
      r->next = q;
      /* set total length of this pbuf and next in chain */
      LWIP_ASSERT("rem_len < max_uint16_t", rem_len < 0xffff);
      q->tot_len = (uint16_t)rem_len;
      /* this pbuf length is pool size, unless smaller sized tail */
      q->len = LWIP_MIN((uint16_t)rem_len, PBUF_POOL_BUFSIZE_ALIGNED);
      q->payload = (void *)((uint8_t *)q + SIZEOF_STRUCT_PBUF);
      LWIP_ASSERT("pbuf_alloc: pbuf q->payload properly aligned",
              ((mem_ptr_t)q->payload % MEM_ALIGNMENT) == 0);
      LWIP_ASSERT("check p->payload + p->len does not overflow pbuf",
                  ((uint8_t*)p->payload + p->len <=
                   (uint8_t*)p + SIZEOF_STRUCT_PBUF + PBUF_POOL_BUFSIZE_ALIGNED));
      q->ref = 1;
      /* calculate remaining length to be allocated */
      rem_len -= q->len;
      /* remember this pbuf for linkage in next iteration */
      r = q;
    }
    /* end of chain */
    /*r->next = NULL;*/

    break;
  case PBUF_RAM:
    /* If pbuf is to be allocated in RAM, allocate memory for it. */
    p = (struct pbuf*)mem_malloc(LWIP_MEM_ALIGN_SIZE(SIZEOF_STRUCT_PBUF + offset) + LWIP_MEM_ALIGN_SIZE(length));
    if (p == NULL) {
      return NULL;
    }
    /* Set up internal structure of the pbuf. */
    p->payload = LWIP_MEM_ALIGN((void *)((uint8_t *)p + SIZEOF_STRUCT_PBUF + offset));
    p->len = p->tot_len = length;
    p->next = NULL;
    p->type = type;

    LWIP_ASSERT("pbuf_alloc: pbuf->payload properly aligned",
           ((mem_ptr_t)p->payload % MEM_ALIGNMENT) == 0);
    break;
  /* pbuf references existing (non-volatile static constant) ROM payload? */
  case PBUF_ROM:
  /* pbuf references existing (externally allocated) RAM payload? */
  case PBUF_REF:
    /* only allocate memory for the pbuf structure */
    p = (struct pbuf *)memp_malloc(MEM_DEBUG);
    if (p == NULL) {
      LWIP_DEBUGF(PBUF_DEBUG | LWIP_DBG_LEVEL_SERIOUS,
                  ("pbuf_alloc: Could not allocate MEMP_PBUF for PBUF_%s.\n",
                  (type == PBUF_ROM) ? "ROM" : "REF"));
      return NULL;
    }
    /* caller must set this field properly, afterwards */
    p->payload = NULL;
    p->len = p->tot_len = length;
    p->next = NULL;
    p->type = type;
    break;
  default:
    LWIP_ASSERT("pbuf_alloc: erroneous type", 0);
    return NULL;
  }
  /* set reference count */
  p->ref = 1;
  /* set flags */
  p->flags = 0;
  LWIP_DEBUGF(PBUF_DEBUG | LWIP_DBG_TRACE, ("pbuf_alloc(length=%"U16_F") == %p\n", length, (void *)p));
  return p;
}