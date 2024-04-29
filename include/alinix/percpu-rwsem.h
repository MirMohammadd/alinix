#ifndef __ALINIX_KERNEL_PERCPU_RWSEM_H
#define __ALINIX_KERNEL_PERCPU_RWSEM_H


#include <alinix/fs.h>
#include <alinix/rcu_sync.h>
#include <alinix/wait.h>

struct percpu_rw_semaphore {
	struct rcu_sync		rss;
	unsigned int 	*read_count;
	wait_queue_head_t	waiters;
	atomic_t		block;
};


#endif // __ALINIX_KERNEL_PERCPU_RWSEM_H