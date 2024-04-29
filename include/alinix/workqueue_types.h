#ifndef __ALINIX_KERNEL_WORK_QUEUES_TYPES_H
#define __ALINIX_KERNEL_WORK_QUEUES_TYPES_H

#include <alinix/list.h>

typedef void (*work_func_t)(struct work_struct *work);

struct work_struct {
	long long data;
	struct list_head entry;
	work_func_t func;
#ifdef CONFIG_LOCKDEP
	struct lockdep_map lockdep_map;
#endif
};

#endif
