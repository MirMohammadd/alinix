#ifndef __ALINIX_KERNEL_PATH_H
#define __ALINIX_KERNEL_PATH_H

#include <alinix/kernel.h>

struct path {
	struct vfsmount *mnt;
	struct dentry *dentry;
} __randomize_layout;

#endif