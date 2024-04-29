#ifndef __ALINIX_KERNEL_UIO_H
#define __ALINIX_KERNEL_UIO_H




#include <alinix/types.h>

#include <alinix/xarray.h>

enum iter_type {
	/* iter types */
	ITER_UBUF,
	ITER_IOVEC,
	ITER_BVEC,
	ITER_KVEC,
	ITER_XARRAY,
	ITER_DISCARD,
};

struct iovec
{
	void *iov_base;	/* BSD uses caddr_t (1003.1g requires void *) */
	size_t iov_len; /* Must be size_t (1003.1g) */
};
struct iov_iter {
	u8 iter_type;
	bool nofault;
	bool data_source;
	size_t iov_offset;
	const struct bio_vec *bvec;
	/*
	 * Hack alert: overlay ubuf_iovec with iovec + count, so
	 * that the members resolve correctly regardless of the type
	 * of iterator used. This means that you can use:
	 *
	 * &iter->__ubuf_iovec or iter->__iov
	 *
	 * interchangably for the user_backed cases, hence simplifying
	 * some of the cases that need to deal with both.
	 */
	union {
		/*
		 * This really should be a const, but we cannot do that without
		 * also modifying any of the zero-filling iter init functions.
		 * Leave it non-const for now, but it should be treated as such.
		 */
		struct iovec __ubuf_iovec;
		struct {
			union {
				/* use iter_iov() to get the current vec */
				const struct iovec *__iov;
				const struct kvec *kvec;
				// const struct bio_vec *bvec;
				struct xarray *xarray;
				void  *ubuf;
			};
			size_t count;
		};
	};
	union {
		unsigned long nr_segs;
		loff_t xarray_start;
	};
};

static inline enum iter_type iov_iter_type(const struct iov_iter *i)
{
	return i->iter_type;
}

static inline size_t iov_iter_count(const struct iov_iter *i)
{
	return i->count;
}

static inline bool iov_iter_is_discard(const struct iov_iter *i)
{
	return iov_iter_type(i) == ITER_DISCARD;
}

#endif