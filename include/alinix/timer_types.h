#ifndef __ALINIX_KERNEL_TIMER_TYPES_H
#define __ALINIX_KERNEL_TIMER_TYPES_H

#include <alinix/types.h>

struct timer_list {
	/*
	 * All fields that change during normal runtime grouped to the
	 * same cacheline
	 */
	struct hlist_node	entry;
	unsigned long		expires;
	void			(*function)(struct timer_list *);
	uint32_t			flags;

#ifdef CONFIG_LOCKDEP
	struct lockdep_map	lockdep_map;
#endif
};

#endif // __ALINIX_KERNEL_TIMER_TYPES_H