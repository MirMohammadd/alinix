#ifndef _HEISEN_KERNEL_SPINLOCK__HPP
#define _HEISEN_KERNEL_SPINLOCK__HPP

#include "types.h"

using namespace LIBHeisenKernel;

#pragma pack(push,1)
typedef struct _spinlock_ {
	size_t value;
}Spinlock;
#pragma pack(pop)

#endif 