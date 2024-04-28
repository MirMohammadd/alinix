#ifndef __ALINIX_KERNEL_DIM_H
#define __ALINIX_KERNEL_DIM_H

#include <alinix/kernel.h>
#include <alinix/math.h>

#define DIM_NEVENTS 64

#define IS_SIGNIFICANT_DIFF(val, ref) \
	((ref) && (((100UL * abs((val) - (ref))) / (ref)) > 10))


#endif /*__ALINIX_KERNEL_DIM_H*/