#ifndef __ALINIX_KERNEL_WAIT_H
#define __ALINIX_KERNEL_WAIT_H


#include <alinix/spinlock_types.h>
#include <alinix/list.h>

struct wait_queue_head {
	spinlock_t		lock;
	struct list_head	head;
};
typedef struct wait_queue_head wait_queue_head_t;

#endif // __ALINIX_KERNEL_WAIT_H