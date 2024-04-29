#ifndef __ALINIX_KERNEL_RCU_SYNC_H
#define __ALINIX_KERNEL_RCU_SYNC_H

#include <alinix/wait.h>

struct rcu_sync {
	int			gp_state;
	int			gp_count;
	wait_queue_head_t	gp_wait;

	struct rcu_head		cb_head;
};

#endif // __ALINIX_KERNEL_RCU_SYNC_H
