#ifndef __ALINIX_KERNEL_COMPILER_TYPES_H
#define __ALINIX_KERNEL_COMPILER_TYPES_H

#define __naked			__attribute__((__naked__)) notrace
#define __naked __attribute__((naked))
#define __clobber_all "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "memory"
#define __clobber_common "r0", "r1", "r2", "r3", "r4", "r5", "memory"

#if defined(_M_IX86)
__naked void unreachable(void)
{
	asm volatile ("					\
	exit;						\
	exit;						\
"	::: __clobber_all);
}
#elif defined(_M_ARM64)
__attribute__((naked)) void unreachable(void) {
    asm volatile (
        "mov x0, #93\n"   // __NR_exit
        "mov x1, #0\n"    // status = 0
        "svc #0\n"        // exit(0)
        "b .\n"           // infinite loop to ensure function does not return
    );
}

#else 
__attribute__((naked)) void unreachable(void) {
    asm volatile (
        "mov x0, #93\n"   // __NR_exit
        "mov x1, #0\n"    // status = 0
        "mov x8, #93\n"   // syscall number for exit
        "svc #0\n"        // syscall
        "b .\n"           // infinite loop to ensure function does not return
    );
}


#endif

#endif
