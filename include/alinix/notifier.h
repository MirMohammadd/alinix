#ifndef __ALINIX_KERNEL_NOTIFIER_H
#define __ALINIX_KERNEL_NOTIFIER_H

#include <alinix/spinlock_types.h>
#include <alinix/mutex_types.h>

struct notifier_block;

typedef	int (*notifier_fn_t)(struct notifier_block *nb,
			unsigned long action, void *data);

struct notifier_block {
	notifier_fn_t notifier_call;
	struct notifier_block  *next;
	int priority;
};

struct atomic_notifier_head {
	spinlock_t lock;
	struct notifier_block  *head;
};

struct blocking_notifier_head {
	// struct rw_semaphore rwsem;
	struct notifier_block  *head;
};

struct raw_notifier_head {
	struct notifier_block  *head;
};

struct srcu_notifier_head {
	struct mutex mutex;
	// struct srcu_usage srcuu;
	// struct srcu_struct srcu;
	struct notifier_block  *head;
};
#endif // __ALINIX_KERNEL_NOTIFIER_H