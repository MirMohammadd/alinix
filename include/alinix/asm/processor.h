#ifndef __ALINIX_KERNEL_PROCESSOR_H
#define __ALINIX_KERNEL_PROCESSOR_H

static inline void local_irq_disable(void)
{
	#if defined(__i386__) && defined(CONFIG_X86)
	asm volatile("msr daifset, #3" : : : "memory");
	#endif //  i386
}


#endif