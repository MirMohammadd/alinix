#ifndef __ALINIX_KERNEL_NET_INCLUDED_MEM_H
#define __ALINIX_KERNEL_NET_INCLUDED_MEM_H

#include <net/opt.h>

#define LWIP_MEM_ALIGN_SIZE(size) (((size) + MEM_ALIGNMENT - 1) & ~(MEM_ALIGNMENT-1))


#endif