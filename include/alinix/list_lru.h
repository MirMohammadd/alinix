#ifndef __ALINIX_KERNEL_LIST_LRU_H
#define __ALINIX_KERNEL_LIST_LRU_H

#include <alinix/types.h>
#include <alinix/list.h>
#include <alinix/list_bl.h>
#include <alinix/spinlock_types.h>

struct list_lru_one {
	struct list_head	list;
	/* may become negative during memcg reparenting */
	long			nr_items;
};

struct list_lru_node {
	/* protects all lists on the node, including per cgroup */
	spinlock_t		lock;
	/* global list, used for the root cgroup in cgroup aware lrus */
	struct list_lru_one	lru;
	long			nr_items;
} ;


struct list_lru {
	struct list_lru_node	*node;
#ifdef CONFIG_MEMCG_KMEM
	struct list_head	list;
	int			shrinker_id;
	bool			memcg_aware;
	struct xarray		xa;
#endif
};

#endif