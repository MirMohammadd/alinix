#ifndef __ALINIX_KERNEL_ASM_H
#define __ALINIX_KERNEL_ASM_H

# define RET    bx      lr

#define outb(_port, _data)  \
    asm volatile("outb %b0, %w1" \
        : \
        : "a" (_data), "Nd" (_port) \
    );


#endif