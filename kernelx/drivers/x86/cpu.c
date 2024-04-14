#include <hal/hal.h>
#include <mm/memory.h>
#include <lib/string.h>

#define cpuid(in, a, b, c, d) asm volatile("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

char *get_cpu_vendor() {
    int eax, ebx, ecx, edx;
    char *v = (char *) kmalloc(sizeof(char) * 32);
    
    cpuid(0, eax, ebx, ecx, edx);
    
    switch(ebx) {
		case 0x756e6547:
	        strcpy(v, "Intel");
	        break;
	    case 0x68747541:
	        strcpy(v, "AMD");
	        break;
	}
	return v;
}