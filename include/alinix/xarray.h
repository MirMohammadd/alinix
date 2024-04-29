#ifndef __ALINIX_KERNEL_X_ARRAY_H
#define __ALINIX_KERNEL_X_ARRAY_H


#include <alinix/spinlock_types.h>
#include <alinix/gfp_types.h>

#define XA_FLAGS_MARK(mark)	(( gfp_t)((1U << 16) << \
						( unsigned)(mark)))


typedef unsigned xa_mark_t;

struct xarray {
	spinlock_t	xa_lock;
/* private: The rest of the data structure is not to be used directly. */
	gfp_t		xa_flags;
	void  *	xa_head;
};

static inline bool xa_marked(const struct xarray *xa, xa_mark_t mark)
{
	return xa->xa_flags & XA_FLAGS_MARK(mark);
}

#endif // __ALINIX_KERNEL_X_ARRAY_H