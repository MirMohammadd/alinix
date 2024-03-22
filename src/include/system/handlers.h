#ifndef _HANDLERS_H
#define _HANDLERS_H

#include <idt.h>
#include <pic8259.h>

//  #define DEBUG 1

#define DIVIDE_ERROR 0
#define DEBUG_EXC 1
#define NMI_INTERRUPT 2
#define BREAKPOINT 3
#define OVERFLOW 4
#define BOUND_RANGE_EXCEED 5
#define INVALID_OPCODE 6
#define DEV_NOT_AVL 7
#define DOUBLE_FAULT 8
#define COPROC_SEG_OVERRUN 9
#define INVALID_TSS 10
#define SEGMENT_NOT_PRESENT 11
#define STACK_SEGMENT_FAULT 12
#define GENERAL_PROTECTION 13
#define PAGE_FAULT 14
#define INT_RSV 15
#define FLOATING_POINT_ERR 16
#define ALIGNMENT_CHECK 17
#define MACHINE_CHECK 18
#define SIMD_FP_EXC 19

#define SWITCH_KERNEL\
	"movl $0x10, %edx;\
	 movw %dx, %ds;\
	 movw %dx, %es;\
	 movw %dx, %fs;"

#define SAVE_CONTEXT\
	"pusha;"\

#define SAVE_CONTEXT_EC\
        "nop;\
         xchgl %eax, (%esp);\
         pushl %ecx;\
         pushl %edx;"\
         SWITCH_KERNEL\
         "pushl %eax;"

#define EXCEPTION(n)\
    __asm__("INT_"#n":"\
	     SAVE_CONTEXT\
             "pushl $"#n";\
             call *(IntTable+(4*"#n"));\
             add $4, %esp;"\
             RESTORE\
             "iret;")

#define EXCEPTION_EC(n)\
    __asm__("INT_"#n":"\
             SAVE_CONTEXT_EC\
             "pushl $"#n";\
             call *(IntTable+(4*"#n"));\
             add $8, %esp;"\
             RESTORE_EC\
             "iret;")

#define IRQ(n)\
    __asm__("INT_"#n":"\
            SAVE_CONTEXT\
            "movl %esp, %eax;"\
	    "pushl %eax;"\
            "call _irqinterrupt;"\
            "popl %eax;"\
            "movl %eax, %esp;"\
            RESTORE\
            "iret;")

#define SYSCALL(n)\
    __asm__("INT_"#n":"\
            SAVE_CONTEXT\
            "call syscall_handler;"\
            RESTORE\
            "iret;")

#define RESTORE \
		"popa;"

#define RESTORE_EC \
        "popl %edx;\
         popl %ecx;\
         popl %eax;"

extern IRQ_s *shareHandler[IRQ_NUM];

extern void (*IntTable[IDT_SIZE])();
void kernel_init_interrupt_function_table();
void kernel_add_interrupt_function_table(int i, void (*func)());
void _globalException(int n, int error);
void _irqinterrupt();
void _int_rsv();

#endif