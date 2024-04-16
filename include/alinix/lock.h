#ifndef __ALINIX_KERNEL_LOCK_H
#define __ALINIX_KERNEL_LOCK_H


void Lock(){
    asm ("pause");
}
#endif