#include <alinix/fs.h>
#include <alinix/uio.h>

extern  filemap_splice_read(struct file *in, loff_t *ppos,
			    struct pipe_inode_info *pipe,
			    size_t len, unsigned int flags);
extern int generic_file_readonly_mmap(struct file *, struct vm_area_struct *);
extern loff_t generic_file_llseek(struct file *file, loff_t offset, int whence);
extern ssize_t generic_file_read_iter(struct kiocb *, struct iov_iter *);
extern ssize_t __generic_file_write_iter(struct kiocb *, struct iov_iter *);
extern ssize_t generic_file_write_iter(struct kiocb *, struct iov_iter *);
extern ssize_t generic_file_direct_write(struct kiocb *, struct iov_iter *);
extern ssize_t generic_perform_write(struct kiocb *, struct iov_iter *);
extern ssize_t direct_write_fallback(struct kiocb *iocb, struct iov_iter *iter,
		ssize_t direct_written, ssize_t buffered_written);

const struct file_operations generic_ro_fops = {
	.llseek		= generic_file_llseek,
	.read_iter	= generic_file_read_iter,
	.mmap		= generic_file_readonly_mmap,
	.splice_read	= filemap_splice_read,
};