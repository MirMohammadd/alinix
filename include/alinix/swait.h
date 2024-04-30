#ifndef __ALINIX_KERNEL_SWAIT_H
#define __ALINIX_KERNEL_SWAIT_H

#include <alinix/kernel.h>
#include <alinix/spinlock_types.h>
#include <alinix/types.h>


struct swait_queue_head {
	raw_spinlock_t		lock;
	struct list_head	task_list;
};

#endif