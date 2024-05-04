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

extern void kernelMain();

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




extern void kernelMain(const multiboot_info_t* mbi, unsigned int multiboot_magic){
    /**
     * @brief Main  function for Kernel Entry Point, implementing all the final actions here
    */
    #ifdef IGNORE_INTERRUPT
    IgnoreInterrupt();
    #endif
    uint32_t kernel_base = (uint32_t) &_kernel_base;
    uint32_t kernel_end = (uint32_t) &_kernel_end;
    uint32_t kernel_size = kernel_end - kernel_base;
    gdbEnabled = true;
    ConsoleInit(true);
    ConsoleClear();
    Log(Info,"Hello!");
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
        asm volatile (
        "mov $0x06, %%ah\n"   // Scroll window up
        "mov $0x00, %%al\n"   // Number of lines to scroll
        "mov $0x1F, %%bh\n"   // Attribute (color)
        "mov $0, %%cx\n"      // Upper left corner (row 0, col 0)
        "mov $0, %%dx\n"      // Lower right corner (row 0, col 0)
        "int $0x10\n"         // Call BIOS video interrupt
        :
        :
        : "ah", "al", "bh", "cx", "dx"
    );

    // Write message to the screen
    asm volatile (
        "mov $0x0E, %%ah\n"   // Teletype output
        "mov $'H', %%al\n"    // Character to print
        "mov $0, %%bh\n"      // Page number
        "mov $0x1F, %%bl\n"   // Attribute (color)
        "int $0x10\n"         // Call BIOS video interrupt
        :
        :
        : "ah", "al", "bh", "bl"
    );
	// for (int i = 0 ; i < 0x100000000 ; i++)
        
    // asm volatile  ("hlt"); 
    // runkernel();
    /////////////////////
    // This should always return 0
    // return 0;
    //////////////////////
}