#ifndef __ALINIX_KERNEL_BASE_BASE_H
#define __ALINIX_KERNEL_BASE_BASE_H

#include <alinix/types.h>
#include <alinix/klist.h>

struct device_private {
	struct klist klist_children;
	struct klist_node knode_parent;
	struct klist_node knode_driver;
	struct klist_node knode_bus;
	struct klist_node knode_class;
	struct list_head deferred_probe;
	struct device_driver *async_driver;
	char *deferred_probe_reason;
	struct device *device;
	uint8_t dead:1;
};

#endif