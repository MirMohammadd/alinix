#ifndef __ALINIX_KERNEL_LOCK_REF_H
#define __ALINIX_KERNEL_LOCK_REF_H

#include <alinix/kernel.h>

struct lockref {
	union {
#if USE_CMPXCHG_LOCKREF
		aligned_u64 lock_count;
#endif
		struct {
			spinlock_t lock;
			int count;
		};
	};
};
#endif // __ALINIX_KERNEL_LOCK_REF_H