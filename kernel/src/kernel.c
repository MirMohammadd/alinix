/**
 * @file kernel.c
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

/**
 * @abstraction:
 *  - Kernel Main entry file.
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
#include <net/dhcp.h>
#include <clock/clock.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("AliNix Kernel")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


void _print_string(const char* str);

extern void print_string();
multiboot_info_t* mbi = 0;
struct hwrpb_struct *hwrpb = INIT_HWRPB;

void clear_screen() {asm ("call clear_screen");}
void init_keyboard(){asm ("call init_keyboard");};
void wait_for_key_press() {asm ("call wait_for_key_press");};
void read_scan_code(){asm ("call read_scan_code");};
void print_scan_code(){asm ("call print_scan_code");};




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


typedef void (*constructor)();
constructor start_ctors;
constructor end_ctors;


/**
 * @brief Function to find the physical address corresponding to a virtual address.
 * 
 * This function takes a virtual address pointer and a virtual page table, and returns the corresponding physical address.
 * 
 * @param vptb Pointer to the virtual page table.
 * @param ptr Void pointer to the virtual address to be translated.
 * @return Void pointer representing the physical address corresponding to the virtual address.
 */
static inline void *find_pa(unsigned long *vptb, void *ptr){
    unsigned long address = (unsigned long )ptr;
    unsigned long result;
    result = vptb[address >> 13];
	result >>= 32;
	result <<= 13;
	result |= address & 0x1fff;
	return (void *) result;
}

/**
 * @brief Prints the string and messages to the video memory
 * @param String to be printed
*/

void _print_string(const char* str)
{
    // VGA text mode buffer
    volatile char* video_memory = (volatile char*)0xb8000;
    // We can change the buffer
    int bufferSize = 80 * 25;
    for(int i = 0; str[i] != '\0' && i < bufferSize; ++i)
    {
        // Each character takes 2 bytes: ASCII and attribute
        video_memory[i*2] = str[i];
        video_memory[i*2+1] = 0x0F; // White text on black background
    }
}



extern void kernelMain(const multiboot_info_t* mbi, unsigned int multiboot_magic){
    /**
     * @brief Main  function for Kernel Entry Point, implementing all the final actions here
    */
    ConsoleClear();
    // #ifdef IGNORE_INTERRUPT
    // IgnoreInterrupt();
    // #endif
    // kernel_panic("Error Error Error!");
    const char* helloMsg = "Hello World!";
    ConsoleInit(true);
    ConsoleClear();
    outportb(0x3D4, *helloMsg);
    inportb(0x60);
    _print_string("Hello World!");
    uint32_t kernel_base = (uint32_t) &_kernel_base;
    uint32_t kernel_end = (uint32_t) &_kernel_end;
    uint32_t kernel_size = kernel_end - kernel_base;
    gdbEnabled = true;
    ForegroundColor = VGA_COLOR_BLUE;
    BackgroundColor = VGA_COLOR_LIGHT_GREY;
    ConsoleClear();
    Clear(45);
    clock_init();
    if(multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        Log(Error,"Error!");
        WriteLine("Error: not booted by a multiboot bootloader");
        return;
    }
    Write("Kernel virtual base: 0x"); printfHex32(_kernel_virtual_base); WriteLine(" ");
    Write("Kernel Base: 0x"); printfHex32(kernel_base);
    WriteLine(" ");
    Write("Kernel End: 0x"); printfHex32(kernel_end); WriteLine("  ");
    Write("Kernel Size: "); Write(IntToString(kernel_size / 1024)); Write(" Kb      ("); Write(IntToString(kernel_size)); WriteLine(")");
    init_keyboard();
    ConsoleInit(true);
    ConsoleClear();
    __print_asm("Starting the kernel....\n");
    Write("Starting the kernel entry...");
    Log(Info,"Hello!");
    beep();
    srm_printk("Starting the Kernel ...\n");
    if (!kernel_base){
        Log(Error,"Panic! Kernel Base is memory corrupted!!");
        kernelMemoryCorruptionLockDown();
    }
    display_model_initialise();
    WriteLine("Booting the kernel");

    srm_printk("Starting the Kheap...\n");
    _print_string("Starting the Kheap..\n");
    Log(Info,"Kheap is getting started...\n");
    kheap_init();
    srm_printk("Started the Kheap\n");
    ProgressBarInit(progressBar,10,15,13,45);

    const char* args = (const char*)phys2virt(mbi->cmdline);
    if (strcmp(args, "gdb")){
        gdbEnabled = true;
    }
    dhcp_start("eth0");
    Log(Info,"Ok\n Now booting the kernel");
    srm_printk(" Ok\nNow booting the kernel\n");

	for (int i = 0 ; i < 0x100000000 ; i++)
        // Do nothing here
    do {
        wait_for_key_press();
        read_scan_code();
        print_scan_code();
    } while (1);
    asm volatile  ("hlt");
}