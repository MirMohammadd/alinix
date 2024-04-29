#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/fs.h>
#include <alinix/err.h>
#include <alinix/uio.h>
#include <alinix/pagevec.h>

#define PAGE_SHIFT 100

static void __filemap_fdatawait_range(struct address_space *mapping,
				     loff_t start_byte, loff_t end_byte);

ssize_t
generic_file_read_iter(struct kiocb *iocb, struct iov_iter *iter)
{
	size_t count = iov_iter_count(iter);
	ssize_t retval = 0;

	if (!count)
		return 0; /* skip atime */

	if (iocb->ki_flags & IOCB_DIRECT) {
		struct file *file = iocb->ki_filp;
		struct address_space *mapping = file->f_mapping;
		struct inode *inode = mapping->host;

		retval = kiocb_write_and_wait(iocb, count);
		if (retval < 0)
			return retval;
		file_accessed(file);

		// retval = mapping->a_ops->direct_IO(iocb, iter);
		if (retval >= 0) {
			iocb->ki_pos += retval;
			count -= retval;
		}
		if (retval != -EIOCBQUEUED)
			iov_iter_revert(iter, count - iov_iter_count(iter));

		/*
		 * Btrfs can have a short DIO read if we encounter
		 * compressed extents, so if there was an error, or if
		 * we've already read everything we wanted to, or if
		 * there was a short read because we hit EOF, go ahead
		 * and return.  Otherwise fallthrough to buffered io for
		 * the rest of the read.  Buffered reads will not work for
		 * DAX files, so don't bother trying.
		 */
		if (retval < 0 || !count || IS_DAX(inode))
			return retval;
		if (iocb->ki_pos >= i_size_read(inode))
			return retval;
	}

	return filemap_read(iocb, iter, retval);
}

int kiocb_write_and_wait(struct kiocb *iocb, size_t count)
{
	struct address_space *mapping = iocb->ki_filp->f_mapping;
	loff_t pos = iocb->ki_pos;
	loff_t end = pos + count - 1;

	if (iocb->ki_flags) {
		if (filemap_range_needs_writeback(mapping, pos, end))
			return -EAGAIN;
		return 0;
	}

	return filemap_write_and_wait_range(mapping, pos, end);
}

int filemap_write_and_wait_range(struct address_space *mapping,
				 loff_t lstart, loff_t lend)
{
	int err = 0, err2;

	if (lend < lstart)
		return 0;

	if (mapping_needs_writeback(mapping)) {
		/*
		 * Even if the above returned error, the pages may be
		 * written partially (e.g. -ENOSPC), so we wait for it.
		 * But the -EIO is special case, it may indicate the worst
		 * thing (e.g. bug) happened, so we avoid waiting for it.
		 */
		if (err != -EIO)
			__filemap_fdatawait_range(mapping, lstart, lend);
	}
	err2 = filemap_check_errors(mapping);
	if (!err)
		err = err2;
	return err;
}

static void __filemap_fdatawait_range(struct address_space *mapping,
				     loff_t start_byte, loff_t end_byte)
{
	pgoff_t index = start_byte >> PAGE_SHIFT;
	pgoff_t end = end_byte >> PAGE_SHIFT;
	struct folio_batch fbatch;
	unsigned nr_folios;

	folio_batch_init(&fbatch);

	while (index <= end) {
		unsigned i;

		// nr_folios = filemap_get_folios_tag(mapping, &index, end,
		// 		PAGECACHE_TAG_WRITEBACK, &fbatch);

		if (!nr_folios)
			break;

	//TODO Fix here
	// 	for (i = 0; i < nr_folios; i++) {
	// 		struct folio *folio = fbatch.folios[i];

	// 		folio_wait_writeback(folio);
	// 		folio_clear_error(folio);
	// 	}
	// 	folio_batch_release(&fbatch);
	// 	cond_resched();
	// }
}
}