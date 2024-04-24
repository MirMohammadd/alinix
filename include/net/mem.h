#ifndef __ALINIX_KERNEL_NET_INCLUDED_MEM_H
#define __ALINIX_KERNEL_NET_INCLUDED_MEM_H

#include <net/opt.h>
#include <alinix/compiler.h>

#define LWIP_MEM_ALIGN_SIZE(size) (((size) + MEM_ALIGNMENT - 1) & ~(MEM_ALIGNMENT-1))
#define LWIP_MEM_ALIGN(addr) ((void *)(((mem_ptr_t)(addr) + MEM_ALIGNMENT - 1) & ~(mem_ptr_t)(MEM_ALIGNMENT-1)))
void  mem_free(void *mem);

#endif