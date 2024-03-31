#include "print.h"

void PrintAsm(const char *msg){
        asm volatile (
        "movl $1, %%eax \n\t"  // syscall number for write
        "movl $1, %%ebx \n\t"  // file descriptor for stdout
        "movl %0, %%ecx \n\t"  // address of the message
        "movl $14, %%edx \n\t" // length of the message
        "int $0x80 \n\t"       // call the kernel
        :
        : "r"(msg)
        : "%eax", "%ebx", "%ecx", "%edx"
    );
}