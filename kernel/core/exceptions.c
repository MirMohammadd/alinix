/**
 * @author Ali Mirmohammad
 * @file exceptions.c
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
 *  - All kernel errors and exceptions are defined here.
*/

#include <alinix/exceptions.h>
#include <alinix/types.h>
#include <alinix/printk.h>
#include <alinix/system.h>
#include <alinix/bootconsole.h>
#include <alinix/enums.h>
#include <alinix/idt.h>
#include <alinix/panic.h>
#include <alinix/register.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel exceptions")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


////////////////////////////////////////////////////
//Global  Variables
bool autoFixPagefaults = false;
uint8_t ExcForegroundColor;

/**
 * @brief Handles the case of a zero division error.
 *
 * This function is called when a division by zero error occurs. It prints an error message to the console, disables all interrupts, waits for the user to press a key, shows the stack trace, and then reboots the system.
 *
 * @param esp The value of the ESP register at the time of the error.
 * @return The value of the ESP register passed as a parameter.
 */
uint32_t DivideByZero(uint32_t esp){
    ExcForegroundColor = VGA_COLOR_RED;   
    WriteLine("Zero division Error");

    // Disable all the interrupts
    DisableInterrupts();

    WriteLine(" Press any key to reboot...");

    ShowStacktrace(esp);

    //TODO Add more here
    Panic();

    return esp; // We don't get here?


} 
/**
 * @brief Handles a page fault exception.
 *
 * This function is called when a page fault exception occurs. It prints an error message to the console, disables all interrupts, retrieves the error address from the CR2 register, retrieves the error code from the CPU state, determines the details of what caused the page fault, prints the details to the console, checks if the memory is intact, maps the error address to physical memory if possible, shows the stack trace, and then reboots the system.
 *
 * @param esp The value of the ESP register at the time of the exception.
 * @return The value of the ESP register passed as a parameter.
 */
uint32_t PageFault(uint32_t esp){
    /**
     * @brief  This function is called when there is a page fault
    */
    ExcForegroundColor = VGA_COLOR_BROWN;

    DisableInterrupts();
    // Disable all the interrupts

    uint32_t errorAddress;
    //////////////////////////////////////////////////////
    asm volatile("mov %%cr2, %0" : "=r" (errorAddress));
    /* The CR2 register contains the address that caused an exception.*/
    //////////////////////////////////////////////////////

    struct CPUState* regs = (struct CPUState*)esp;

    // The error code gives us details of what happened.
    int present   = !(regs->ErrorCode & 0x1); // Page not present
    int rw = regs->ErrorCode & 0x2;           // Write operation?
    int us = regs->ErrorCode & 0x4;           // Processor was in user-mode?
    int reserved = regs->ErrorCode & 0x8;     // Overwritten CPU-reserved bits of page entry?
    int id = regs->ErrorCode & 0x10;          // Caused by an instruction fetch?

    Write("Got Page Fault (");

    if(present)
        Write("present ");
    if(rw)
        Write("read-only ");
    if(us)
        Write("user-mode ");
    if(reserved)
        Write("reserved ");
    if(id)
        Write("instruction fetch ");

    Write(") at 0x");
    printfHex32(errorAddress);
    Write(" EIP: 0x");
    printfHex32(regs->EIP);

    Write(" Memory Intact: ");
    if(CheckForErrors())
        Write(" No ");
    else
        Write(" Yes ");
    //////////////////////////////////
    //? Uncomment this?
    // if(scheduler != 0 && scheduler->CurrentProcess() != 0 && scheduler->CurrentProcess()->fileName != 0) {
    //     Write(" Process: ");
    //     WriteLine(scheduler->CurrentProcess()->fileName);
    // }

    if(autoFixPagefaults && present) //Identity map error address
    {
        void* ptr = (void*)errorAddress;
        mapVirtualToPhysical(ptr, ptr, true, true); //Readonly is probably a good idea        
        
        WriteLine(" Fixed pagefault");
        return esp;
    }
    WriteLine(" ..");

    ShowStacktrace(esp);
    Panic();
    return esp; // Shouldn't get here
}

ShowStacktrace(uint32_t esp){
    /*Keep Here empty*/
}

void DisablePagefaultAutoFix(){
    
}

void EnablePagefaultAutoFix(){
    
}