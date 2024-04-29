#ifndef __ALINIX_KERNEL_LIB_GCC_H
#define __ALINIX_KERNEL_LIB_GCC_H

struct DWstruct {
	int high, low;
};

typedef union {
	struct DWstruct s;
	long long ll;
} DWunion;

#endif