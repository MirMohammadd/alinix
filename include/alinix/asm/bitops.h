#ifndef _____BITOPS_H
#define ____BITOPS_H

#include <alinix/types.h>

#define BITS_PER_LONG 32

#define _IOMMU_TEST_CMD(x) IOMMU_TEST_CMD
# define __BITS_PER_LONG 32
/* Imported from include/asm-generic/bitops/generic-non-atomic.h */
#define BITS_PER_BYTE 8
#define BITS_PER_LONG __BITS_PER_LONG
#define BIT_MASK(nr) (1UL << ((nr) % __BITS_PER_LONG))
#define BIT_WORD(nr) ((nr) / __BITS_PER_LONG)

static inline void
set_bit(unsigned long nr, volatile void * addr)
{
	unsigned long temp;
	int *m = ((int *) addr) + (nr >> 5);

	__asm__ __volatile__(
	"1:	ldl_l %0,%3\n"
	"	bis %0,%2,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m)
	:"Ir" (1UL << (nr & 31)), "m" (*m));
}

static inline bool test_bit(unsigned int nr, unsigned long *addr)
{
	return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG - 1)));
}


#endif