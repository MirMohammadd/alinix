#ifndef __ALINIX_KERNEL_DEF_H_INCLUDED_NET
#define __ALINIX_KERNEL_DEF_H_INCLUDED_NET


#include <alinix/types.h>

#define ntohl(x) lwip_ntohl(x)

uint32_t __always_inline
lwip_ntohl(uint32_t n)
{
  return lwip_htonl(n);
}



#define LWIP_MAX(x , y)  (((x) > (y)) ? (x) : (y))
#define LWIP_MIN(x , y)  (((x) < (y)) ? (x) : (y))

#endif