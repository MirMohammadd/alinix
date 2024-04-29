#ifndef __ALINIX_KERNEL_MOUNT_H
#define __ALINIX_KERNEL_MOUNT_H

#include <alinix/kernel.h>

struct vfsmount {
	struct dentry *mnt_root;	/* root of the mounted tree */
	struct super_block *mnt_sb;	/* pointer to superblock */
	int mnt_flags;
	struct mnt_idmap *mnt_idmap;
} __randomize_layout;

#endif // 