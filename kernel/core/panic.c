/**
 * @author Ali Mirmohammad
 * @file panic.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Provides util for when the kernel is panic.
*/

#include <alinix/panic.h>
#include <alinix/log.h>
#include <alinix/idt.h>
#include <alinix/enums.h>
#include <alinix/types.h>
#include <alinix/asm/processor.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Panic module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


/**
 * @ref https://github.com/torvalds/linux/blob/master/kernel/panic.c#L60
*/


#define PANIC_BUFFER_SIZE 1024

static int pause_on_oops;
static int pause_on_oops_flag;
static DEFINE_SPINLOCK(pause_on_oops_lock);
bool crash_kexec_post_notifiers;
int panic_on_warn ;
unsigned long panic_on_taint;
bool panic_on_taint_nousertaint = false;

void Panic(){
    Log(Error, "-------------------------------");
    Log(Error, "--------- Kernel Halted -------");
    Log(Error, "-------------------------------");

    DisableInterrupts();
    while(1) {
        asm("hlt");
    }
}

void kernel_panic(const char *fmt, ...){
    Log(Error, "-------------------------------");
    Log(Error, "--------- Kernel Halted -------");
    Log(Error, "-------------------------------");
    static char buff_size[PANIC_BUFFER_SIZE];
    va_list args;
    long i, i_next = 0,len;
    int old_cpu, this_cpu;
	bool _crash_kexec_post_notifiers = crash_kexec_post_notifiers;

    if (panic_on_warn){
        panic_on_warn = 0; // Set to false
    }
    local_irq_disable();

    old_cpu = PANIC_CPU_INVALID;
    	// preempt_disable_notrace();
}
