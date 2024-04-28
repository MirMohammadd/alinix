#ifndef __ALINIX_KERNEL_PROCESSOR_H
#define __ALINIX_KERNEL_PROCESSOR_H

static inline void local_irq_disable(void)
{
	asm volatile("msr daifset, #3" : : : "memory");
}


#endif