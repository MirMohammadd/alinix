#ifndef __ALINIX_KERNEL_MUTEX_TYPES_H
#define __ALINIX_KERNEL_MUTEX_TYPES_H


#include <alinix/spinlock_types.h>
#include <alinix/list.h>

struct mutex {

#ifdef CONFIG_MUTEX_SPIN_ON_OWNER
	struct optimistic_spin_queue osq; /* Spinner MCS lock */
#endif
	struct list_head	wait_list;
#ifdef CONFIG_DEBUG_MUTEXES
	void			*magic;
#endif
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map	dep_map;
#endif
};

#endif //__ALINIX_KERNEL_MUTEX_TYPES_H