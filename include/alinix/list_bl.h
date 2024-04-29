#ifndef __ALINIX_KERNEL_LIST_BL_H
#define __ALINIX_KERNEL_LIST_BL_H

#include <alinix/list.h>

struct hlist_bl_head {
	struct hlist_bl_node *first;
};

#endif
