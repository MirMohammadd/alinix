#ifndef __ALINIX_KERNEL_IO_DEV_H
#define __ALINIX_KERNEL_IO_DEV_H

#include <alinix/types.h>

struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	unsigned long desc;
	struct resource *parent, *sibling, *child;
};

#endif