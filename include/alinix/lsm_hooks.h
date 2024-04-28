#ifndef __ALINIX_KERNEL_LSM_HOOKS_H
#define __ALINIX_KERNEL_LSM_HOOKS_H

#include <alinix/types.h>

union security_list_options {
	#define LSM_HOOK(RET, DEFAULT, NAME, ...) RET (*NAME)(__VA_ARGS__);
	#undef LSM_HOOK
};

struct lsm_id {
	const char	*name;
	uint64_t	id;
};


struct security_hook_list {
	struct hlist_node		list;
	struct hlist_head		*head;
	union security_list_options	hook;
	const struct lsm_id		*lsmid;
} __randomize_layout;


#endif // __ALINIX_KERNEL_LSM_HOOKS_H