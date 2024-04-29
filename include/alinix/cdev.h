#ifndef __ALINIX_KERNEL_C_DEV_H
#define __ALINIX_KERNEL_C_DEV_H

#include <alinix/types.h>
#include <alinix/kobject.h>
#include <alinix/fs.h>

struct cdev {
	struct kobject kobj;
	// struct module *owner;
	const struct file_operations *ops;
	struct list_head list;
	dev_t dev;
	unsigned int count;
} __randomize_layout;

#endif // __ALINIX_KERNEL_C_DEV_H