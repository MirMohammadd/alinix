#include <alinix/kernel.h>
#include <alinix/asm/console.h>


long srm_puts(const char* str,long len){
    long remaining,written;

    for (remaining = len;remaining > 0;remaining -= written){
        // written = callback_puts(0,str,remaining);
        written &= 0xffffffff;
        str += written;
    }
    return len;
}