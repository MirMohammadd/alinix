#ifndef _ALINIX_KERNEL_ERR_H
#define _ALINIX_KERNEL_ERR_H

#include <alinix/compiler_types.h>


static inline long  PTR_ERR(const void *ptr)
{
	return (long) ptr;
}

#endif