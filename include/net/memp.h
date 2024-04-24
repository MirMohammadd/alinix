#ifndef __ALINIX_KERNEL_NET_MEMP_H
#define __ALINIX_KERNEL_NET_MEMP_H


#include <alinix/types.h>
#include <alinix/memory.h>

extern const uint16_t memp_sizes[MEMP_MAX];


#define memp_malloc(type)     mem_malloc(memp_sizes[type])



#endif