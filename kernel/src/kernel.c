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
multiboot_info_t* mbi = 0;

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

int kernelMain(){
    /**
     * @brief Main  function for Kernel Entry Point, implementing all the final actions here
    */
    uint32_t kernel_base = (uint32_t) &_kernel_base;
    uint32_t kernel_end = (uint32_t) &_kernel_end;
    uint32_t kernel_size = kernel_end - kernel_base;


    const char* args = (const char*)phys2virt(mbi->cmdline);
    if (strcmp(args, "gdb")){
        gdbEnabled = true;
    }

    /////////////////////
    // This should always return 0
    return 0;
    //////////////////////
}