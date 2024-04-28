#ifndef __ALINIX_KERNEL_RCU_LIST_H
#define __ALINIX_KERNEL_RCU_LIST_H


#include <alinix/types.h>

static inline void hlist_add_tail_rcu(struct hlist_node *n,
				      struct hlist_head *h)
{
	struct hlist_node *i, *last = NULL;

	/* Note: write side code, so rcu accessors are not needed. */
	for (i = h->first; i; i = i->next)
		last = i;

	if (last) {
		n->next = last->next;
	} 
}

#endif