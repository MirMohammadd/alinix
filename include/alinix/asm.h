#ifndef __ALINIX_KERNEL_ASM_H
#define __ALINIX_KERNEL_ASM_H

# define RET    bx      lr

#define outb( _port, _data)  \
    asm volatile("outb %1, %0" \
        : \
        : "dN"(_port), "a" (_data) \
    );


#endif