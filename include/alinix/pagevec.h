#ifndef __ALINIX_KERNEL_PAGE_VEC_H
#define __ALINIX_KERNEL_PAGE_VEC_H

#include <alinix/types.h>
#define MIN_NR_GENS		2U
#define MAX_NR_GENS		4U
#define WORKINGSET_ANON 0
#define WORKINGSET_FILE 1
#define ANON_AND_FILE 2
#define MAX_NR_ZONES 4
struct folio_batch {
	struct list_head folios[MAX_NR_GENS][ANON_AND_FILE][MAX_NR_ZONES];
	unsigned char nr;
	unsigned char i;
	bool percpu_pvec_drained;
	// struct folio *folios[PAGEVEC_SIZE];
};

#endif