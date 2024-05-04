#ifndef __ALINIX_KERNEL_BEEP_H
#define __ALINIX_KERNEL_BEEP_H

#include <alinix/port.h>

void beep() {
    outportb(0xB6, 0x43);
    outportb(30, 0x42);
    outportb(5, 0x42);
    
    outportb(inportb(0x61) | 3, 0x61);
}


#endif // 