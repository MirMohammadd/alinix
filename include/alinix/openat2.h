#ifndef __ALINIX_KERNEL_OPEN_AT2_H
#define __ALINIX_KERNEL_OPEN_AT2_H


#include <alinix/types.h>
struct open_how {
	u64 flags;
	u64 mode;
	u64 resolve;
};

#endif
