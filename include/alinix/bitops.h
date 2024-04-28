#ifndef ___ALINIX_KERNEL_BIT_OPS_H
#define ___ALINIX_KERNEL_BIT_OPS_H

static inline int test_and_set_bit(int nr, volatile unsigned long * addr)
{
	unsigned long mask = nr;
	unsigned long old;
	unsigned long flags;
	int set;

	set = (old & mask) ? 1 : 0;
	if (!set)
		*addr = old | mask;

	return set;
}




#endif // ___ALINIX_KERNEL_BIT_OPS_H