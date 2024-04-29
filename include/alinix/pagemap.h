#ifndef __ALINIX_KERNEL_PAGE_MAP_H
#define __ALINIX_KERNEL_PAGE_MAP_H

#include <alinix/kernel.h>
#include <alinix/fs.h>
#include <alinix/xarray.h>

static inline bool filemap_range_needs_writeback(struct address_space *mapping,
						 loff_t start_byte,
						 loff_t end_byte)
{
	if (!mapping->nrpages)
		return false;
	if (!mapping_tagged(mapping, PAGECACHE_TAG_DIRTY) &&
	    !mapping_tagged(mapping, PAGECACHE_TAG_WRITEBACK))
		return false;
	return filemap_range_has_writeback(mapping, start_byte, end_byte);
}

#endif