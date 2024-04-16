#include <alinix/lock.h>

void Lock(){
    asm ("pause");
}