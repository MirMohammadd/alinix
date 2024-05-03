/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

#include <alinix/types.h>
#include <alinix/memory.h>
#include <alinix/string.h>
#include <alinix/multiboot.h>
#include <alinix/system.h>
#include <alinix/printk.h>
#include <alinix/kernel.h>
#include <alinix/idt.h>
#include <alinix/assembly.h>
#include <alinix/audit.h>
#include <alinix/security.h>
#include <alinix/inet.h>
#include <alinix/init.h>
#include <asm/setup.h>

multiboot_info_t* mbi = 0;
struct hwrpb_struct *hwrpb = INIT_HWRPB;

/// @brief //////
// Basic global vars for kernel
//! These variables should be static
static uint32_t _kernel_base;
static uint32_t _kernel_end;
static uint32_t  _kernel_virtual_base;
static uint32_t stack_top;

// bool gdbEnabled;

typedef void (*constructor)();
constructor start_ctors;
constructor end_ctors;
void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

static inline void *find_pa(unsigned long *vptb, void *ptr){
    unsigned long address = (unsigned long )ptr;
    unsigned long result;
    result = vptb[address >> 13];
	result >>= 32;
	result <<= 13;
	result |= address & 0x1fff;
	return (void *) result;
}

#if defined(__i386__) || defined(_M_IX86) || defined(__x86_64__) || defined(_M_X64)
static inline void
runkernel(void)
{
	__asm__ __volatile__(
		"bis %0,%0,$27\n\t"
		"jmp ($27)"
		: /* no outputs: it doesn't even return */
		: "r" (START_ADDR));
}

#elif defined(__arm__) || defined(__aarch64__) || defined(__arm64__) || defined(__aarch64__)

static inline void runkernel(void){
    asm volatile(
        "adrp x0, %0\n\t"
        "add x0, x0, :lo12:%0\n\t"
        "br x0"
        :
        : "p"(START_ADDR)
        : "x0"
    );
}

#endif 


int kernelMain(){
    /**
     * @brief Main  function for Kernel Entry Point, implementing all the final actions here
    */
    #ifdef IGNORE_INTERRUPT
    IgnoreInterrupt();
    #endif
    uint32_t kernel_base = (uint32_t) &_kernel_base;
    uint32_t kernel_end = (uint32_t) &_kernel_end;
    uint32_t kernel_size = kernel_end - kernel_base;
    srm_printk("Starting the Kernel ...\n");
    if (!kernel_base){
        kernelMemoryCorruptionLockDown();
        return -1;
    }
    display_model_initialise();

    srm_printk("Starting the Kheap...\n");
    kheap_init();
    srm_printk("Started the Kheap\n");

    const char* args = (const char*)phys2virt(mbi->cmdline);
    if (strcmp(args, "gdb")){
        gdbEnabled = true;
    }
    // dhcp_start("eth0");
    srm_printk(" Ok\nNow booting the kernel\n");
	for (int i = 0 ; i < 0x100000000 ; i++)
        
    // asm volatile  ("hlt"); 
    runkernel();
    /////////////////////
    // This should always return 0
    return 0;
    //////////////////////
}