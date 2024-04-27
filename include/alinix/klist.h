#ifndef __ALINIX_KERNEL_K_LIST_H    
#define __ALINIX_KERNEL_K_LIST_H

#include <alinix/types.h>

typedef struct refcount_struct {
	atomic_t refs;
} refcount_t;

typedef struct refcount_struct {
	atomic_t refs;
} refcount_t;

struct kref {
	refcount_t refcount;
};

struct klist_node {
	void			*n_klist;	/* never access directly */
	struct list_head	n_node;
	struct kref		n_ref;
};

extern int klist_node_attached(struct klist_node *n);

#endif