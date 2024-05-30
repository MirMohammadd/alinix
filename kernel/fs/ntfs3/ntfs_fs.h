/**
 * @file ntfs_fs.h
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 * 	- Kernel NTFS file system header file.
*/
#ifndef __ALINIX_KERNEL_FS_NTFS3_H_FS
#define __ALINIX_KERNEL_FS_NTFS3_H_FS

#include <alinix/init.h>

struct ntfs_sb_info {
	struct super_block *sb;

	u32 discard_granularity;
	u64 discard_granularity_mask_inv; // ~(discard_granularity_mask_inv-1)

	u32 cluster_size; // bytes per cluster
	u32 cluster_mask; // == cluster_size - 1
	u64 cluster_mask_inv; // ~(cluster_size - 1)
	u32 block_mask; // sb->s_blocksize - 1
	u32 blocks_per_cluster; // cluster_size / sb->s_blocksize

	u32 record_size;
	u32 index_size;

	u8 cluster_bits;
	u8 record_bits;

	u64 maxbytes; // Maximum size for normal files.
	u64 maxbytes_sparse; // Maximum size for sparse file.

	unsigned long flags; // See NTFS_FLAGS_

	u64 zone_max; // Maximum MFT zone length in clusters
	u64 bad_clusters; // The count of marked bad clusters.

	u16 max_bytes_per_attr; // Maximum attribute size in record.
	u16 attr_size_tr; // Attribute size threshold (320 bytes).

	/* Records in $Extend. */
	u64 objid_no;
	u64 quota_no;
	u64 reparse_no;
	u64 usn_jrnl_no;
};

#endif /*__ALINIX_KERNEL_FS_NTFS3_H_FS*/