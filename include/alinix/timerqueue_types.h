#ifndef __ALINIX_KERNEL_TIMER_QUEUE_TYPES_H
#define __ALINIX_KERNEL_TIMER_QUEUE_TYPES_H

#include <alinix/types.h>
#include <alinix/rbtree_types.h>

struct timerqueue_node {
	struct rb_node node;
	ktime_t expires;
};



#endif // __ALINIX_KERNEL_TIMER_QUEUE_TYPES_H