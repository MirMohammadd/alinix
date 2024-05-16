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


/**
 * @abstraction:
 *  - Provides RTC and system clock utility.
*/

#include <alinix/system.h>
#include <alinix/init.h>
#include <alinix/kernel.h>
#include <clock/clock.h>

#define	UMODE	0170000
#define	SCHMAG	10

/**
 * * Defines the clock for the system 
*/

/**
 * @ref https://wiki.osdev.org/Real_Time_Clock
 * @note Needed ports for RTC (real time clock) are : 
 * *0x70
 * * 0x71
 * @note Port 0x70 is used to specify an index or "register number" and disable NMI
 * @note Port 0x71 is used to read or write from/to that byte of CMOS configuration
 * 
*/

PRIVATE __always_inline VOID __setup_registers(){
    /**
     * @warning no interrupts should have happen here
    */

    DisableInterrupts(); // This will run cli in assembly
    outportb(0x70,0x8A); // select Status Register A, and disable NMI (by setting the 0x80 bit)
    outportb(0x71, 0x20);	// write to CMOS/RTC RAM
    EnableInterrupts(); // Run sti 
}

void inline change_interrupts_rate(int frequency,int rate){
    rate &= 0x0F;
    DisableInterrupts();
    outportb(0x70, 0x8A);		// set index to register A, disable NMI
    char prev= (char) inportb(0x71);	// get initial value of register A
    outportb(0x70, 0x8A);		// reset index to A
    outportb(0x71, (prev & 0xF0) | rate); //write only our rate to A. Note, rate is the bottom 4 bits.
    EnableInterrupts();
}

void inline __select_C_register(){
    outportb(0x70, 0x0C);	// select register C
    inportb(0x71);		// just throw away contents
}

VOID clock_init(){
    __setup_registers();
    change_interrupts_rate(0, 0); // Specify your desired frequency and rate here
    __select_C_register();
}