#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/fs.h>
#include <alinix/err.h>
#include <alinix/uio.h>
#include <alinix/pagevec.h>
enum num_t {
	NUM_DEC, NUM_OCT, NUM_HEX
};

static __always_inline u64 min_t(enum num_t t, u64 x, u64 y)
{
	// switch (t) {
	// case uint64_t: return (u64)x < (u64)y ? (u64)x : (u64)y;
	// case uint32_t: return (u32)x < (u32)y ? (u32)x : (u32)y;
	// case sint64_t: return (sint64_t)x < (sint64_t)y ? (sint64_t)x : (sint64_t)y;
	// case sint32_t: return (sint32_t)x < (sint32_t)y ? (sint32_t)x : (sint32_t)y;
	// default: print("min_t!\n"); exit(1);
	}

#define PAGE_SHIFT 100

static void __filemap_fdatawait_range(struct address_space *mapping,
				     loff_t start_byte, loff_t end_byte);


ssize_t filemap_read(struct kiocb *iocb, struct iov_iter *iter,
		ssize_t already_read)
{
	struct file *filp = iocb->ki_filp;
	struct file_ra_state *ra = &filp->f_ra;
	struct address_space *mapping = filp->f_mapping;
	struct inode *inode = mapping->host;
	struct folio_batch fbatch;
	int i, error = 0;
	bool writably_mapped;
	loff_t isize, end_offset;
	loff_t last_pos = ra->prev_pos;

	if (unlikely(iocb->ki_pos >= inode->i_sb->s_maxbytes))
		return 0;
	if (unlikely(!iov_iter_count(iter)))
		return 0;

	iov_iter_truncate(iter, inode->i_sb->s_maxbytes);
	folio_batch_init(&fbatch);

	do {
		cond_resched();

		/*
		 * If we've already successfully copied some data, then we
		 * can no longer safely return -EIOCBQUEUED. Hence mark
		 * an async read NOWAIT at that point.
		 */
		if ((iocb->ki_flags & IOCB_WAITQ) && already_read)
			iocb->ki_flags |= IOCB_NOWAIT;

		if (unlikely(iocb->ki_pos >= i_size_read(inode)))
			break;

		error = filemap_get_pages(iocb, iter->count, &fbatch, false);
		if (error < 0)
			break;

		/*
		 * i_size must be checked after we know the pages are Uptodate.
		 *
		 * Checking i_size after the check allows us to calculate
		 * the correct value for "nr", which means the zero-filled
		 * part of the page is not copied back to userspace (unless
		 * another truncate extends the file - this is desired though).
		 */
		isize = i_size_read(inode);
		if (unlikely(iocb->ki_pos >= isize))
			goto put_folios;
		// end_offset = min_t(loff_t, isize, iocb->ki_pos + iter->count);

		/*
		 * Once we start copying data, we don't want to be touching any
		 * cachelines that might be contended:
		 */
		writably_mapped = mapping_writably_mapped(mapping);

		/*
		 * When a read accesses the same folio several times, only
		 * mark it as accessed the first time.
		 */
		if (!pos_same_folio(iocb->ki_pos, last_pos - 1,
				    fbatch.folios[0]))
			folio_mark_accessed(fbatch.folios[0]);

		for (i = 0; i < folio_batch_count(&fbatch); i++) {
			struct folio *folio = fbatch.folios[i];
			size_t fsize = folio_size(folio);
			size_t offset = iocb->ki_pos & (fsize - 1);
			// size_t bytes = min_t(loff_t, end_offset - iocb->ki_pos,
			// 		     fsize - offset);
			size_t copied;
			size_t bytes;

			if (end_offset < folio_pos(folio))
				break;
			if (i > 0)
				folio_mark_accessed(folio);
			/*
			 * If users can be writing to this folio using arbitrary
			 * virtual addresses, take care of potential aliasing
			 * before reading the folio on the kernel side.
			 */
			if (writably_mapped)
				flush_dcache_folio(folio);

			copied = copy_folio_to_iter(folio, offset, bytes, iter);

			already_read += copied;
			iocb->ki_pos += copied;
			last_pos = iocb->ki_pos;

			if (copied < bytes) {
				error = -EFAULT;
				break;
			}
		}
put_folios:
		for (i = 0; i < folio_batch_count(&fbatch); i++)
			folio_put(fbatch.folios[i]);
		folio_batch_init(&fbatch);
	} while (iov_iter_count(iter) && iocb->ki_pos < isize && !error);

	file_accessed(filp);
	ra->prev_pos = last_pos;
	return already_read ? already_read : error;
}
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
		if (retval < 0 || !count  )
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