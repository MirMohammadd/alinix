#ifndef __IOMMUFD_UTILS_H
#define __IOMMUFD_UTILS_H

# define __BITS_PER_LONG 32
#define BITS_PER_BYTE 8
#define BITS_PER_LONG __BITS_PER_LONG
#define BIT_MASK(nr) (1UL << ((nr) % __BITS_PER_LONG))
#define BIT_WORD(nr) ((nr) / __BITS_PER_LONG)

static inline void set_bit(unsigned int nr, unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);

	*p |= mask;
}

static inline bool test_bit(unsigned int nr, unsigned long *addr)
{
	return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG - 1)));
}


#endif

