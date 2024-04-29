#ifndef __ALINIX_KERNEL_PAGE_VEC_H
#define __ALINIX_KERNEL_PAGE_VEC_H

#include <alinix/types.h>

struct folio_batch {
	unsigned char nr;
	unsigned char i;
	bool percpu_pvec_drained;
	// struct folio *folios[PAGEVEC_SIZE];
};

#endif