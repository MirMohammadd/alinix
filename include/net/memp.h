#ifndef __ALINIX_KERNEL_NET_MEMP_H
#define __ALINIX_KERNEL_NET_MEMP_H


#include <alinix/types.h>

#define memp_malloc(type)     mem_malloc(memp_sizes[type])


extern const uint16_t memp_sizes[MEMP_MAX];

#endif