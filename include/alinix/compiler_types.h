#ifndef __ALINIX_KERNEL_COMPILER_TYPES_H
#define __ALINIX_KERNEL_COMPILER_TYPES_H

#define __naked			__attribute__((__naked__)) notrace
#define __naked __attribute__((naked))
#define __clobber_all "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "memory"
#define __clobber_common "r0", "r1", "r2", "r3", "r4", "r5", "memory"


__naked void unreachable(void)
{
	asm volatile ("					\
	exit;						\
	exit;						\
"	::: __clobber_all);
}


#endif
