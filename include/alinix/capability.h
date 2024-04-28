#ifndef __ALINIX_KERNEL_CAPABILITY_H
#define __ALINIX_KERNEL_CAPABILITY_H

#include <alinix/types.h>

#define CAP_SYS_TIME 25
#define	EPERM		 1	/* Operation not permitted */

static inline bool capable(int cap)
{
	return true;
}

#endif // __ALINIX_KERNEL_CAPABILITY_H