#ifndef __ALINIX_KERNEL_DEF_H_INCLUDED_NET
#define __ALINIX_KERNEL_DEF_H_INCLUDED_NET


#include <alinix/types.h>

#define ntohl(x) lwip_ntohl(x)

uint32_t __always_inline
lwip_ntohl(uint32_t n)
{
  return lwip_htonl(n);
}


#if BYTE_ORDER == BIG_ENDIAN
#define lwip_htons(x) (x)
#define lwip_ntohs(x) (x)
#define lwip_htonl(x) (x)
#define lwip_ntohl(x) (x)
#define PP_HTONS(x) (x)
#define PP_NTOHS(x) (x)
#define PP_HTONL(x) (x)
#define PP_NTOHL(x) (x)
#else /* BYTE_ORDER != BIG_ENDIAN */
#if LWIP_PLATFORM_BYTESWAP
#define lwip_htons(x) LWIP_PLATFORM_HTONS(x)
#define lwip_ntohs(x) LWIP_PLATFORM_HTONS(x)
#define lwip_htonl(x) LWIP_PLATFORM_HTONL(x)
#define lwip_ntohl(x) LWIP_PLATFORM_HTONL(x)
#else /* LWIP_PLATFORM_BYTESWAP */
uint16_t lwip_htons(uint16_t x);
uint16_t lwip_ntohs(uint16_t x);
uint32_t lwip_htonl(uint32_t x);
uint32_t lwip_ntohl(uint32_t x);

#endif /* LWIP_PLATFORM_BYTESWAP */


#define LWIP_MAX(x , y)  (((x) > (y)) ? (x) : (y))
#define LWIP_MIN(x , y)  (((x) < (y)) ? (x) : (y))

#endif