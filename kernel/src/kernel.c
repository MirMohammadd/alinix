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

void _print_string(const char* str);

extern void kernelMain();
extern void print_string();
multiboot_info_t* mbi = 0;
struct hwrpb_struct *hwrpb = INIT_HWRPB;




extern uint32_t _kernel_base;
extern uint32_t _kernel_end;
extern uint32_t _kernel_virtual_base;
extern uint32_t stack_top;

typedef void (*constructor)();
extern constructor start_ctors;
extern constructor end_ctors;
extern void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern void _set_debug_traps();

/// @brief //////
// Basic global vars for kernel
//! These variables should be static
extern uint32_t _kernel_base;
extern uint32_t _kernel_end;
extern uint32_t  _kernel_virtual_base;
extern uint32_t stack_top;

// bool gdbEnabled;

typedef void (*constructor)();
constructor start_ctors;
constructor end_ctors;
// extern void callConstructors()
// {
//     for(constructor* i = &start_ctors; i != &end_ctors; i++)
//         (*i)();
// }

static inline void *find_pa(unsigned long *vptb, void *ptr){
    unsigned long address = (unsigned long )ptr;
    unsigned long result;
    result = vptb[address >> 13];
	result >>= 32;
	result <<= 13;
	result |= address & 0x1fff;
	return (void *) result;
}

void _print_string(const char* str)
{
    // VGA text mode buffer
    volatile char* video_memory = (volatile char*)0xb8000;
    for(int i = 0; str[i] != '\0'; ++i)
    {
        // Each character takes 2 bytes: ASCII and attribute
        video_memory[i*2] = str[i];
        video_memory[i*2+1] = 0x0F; // White text on black background
    }
}



void kernelMain(const multiboot_info_t* mbi, unsigned int multiboot_magic){
    /**
     * @brief Main  function for Kernel Entry Point, implementing all the final actions here
    */
    #ifdef IGNORE_INTERRUPT
    IgnoreInterrupt();
    #endif
    _print_string("Hello World!");
    uint32_t kernel_base = (uint32_t) &_kernel_base;
    uint32_t kernel_end = (uint32_t) &_kernel_end;
    uint32_t kernel_size = kernel_end - kernel_base;
    gdbEnabled = true;
    ConsoleInit(true);
    ConsoleClear();
    Log(Info,"Hello!");
    beep();
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
        
    asm volatile  ("hlt"); 
    // runkernel();
    /////////////////////
    // This should always return 0
    // return 0;
    //////////////////////
}