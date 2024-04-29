#ifndef __ALINIX_KERNEL_X_ARRAY_H
#define __ALINIX_KERNEL_X_ARRAY_H


#include <alinix/spinlock_types.h>
#include <alinix/gfp_types.h>

struct xarray {
	spinlock_t	xa_lock;
/* private: The rest of the data structure is not to be used directly. */
	gfp_t		xa_flags;
	void  *	xa_head;
};

#endif // __ALINIX_KERNEL_X_ARRAY_H