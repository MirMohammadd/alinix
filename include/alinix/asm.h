#ifndef __ALINIX_KERNEL_ASM_H
#define __ALINIX_KERNEL_ASM_H

# define RET    bx      lr

inline void outb(unsigned short _port, unsigned char _data) {
    asm volatile("outb %1, %0"
        :
        : "dN"(_port), "a" (_data)
    );
}

#endif