/**
 * @author Ali Mirmohammad
 * @file fpu.c
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
 * 	- Provides the utility for FPU.
 * 	- Define the needed functions for FPU.
*/
#include <alinix/fpu.h>
#include <alinix/memory.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("FPU module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

/**
 * Enable the Floating Point Unit (FPU) and set the control word for floating point operations.
 *
 * This function enables the FPU by modifying the CR4 register and sets the control word for
 * floating point operations. It initializes a `FPUControlWord` struct and sets the exception
 * masks for invalid operations, divide by zero, overflow, underflow, and precision. It also sets
 * the precision control and rounding control fields of the control word. Finally, it loads the
 * control word into the FPU using the `fldcw` instruction.
 *
 * Note: This function assumes that the FPU was previously disabled before calling it.
 *
 * @return void
 */
void Enable(){
    	uint32_t cr4;
	asm volatile ("mov %%cr4, %0" : "=r"(cr4));
	cr4 |= 0x200;
	asm volatile ("mov %0, %%cr4" :: "r"(cr4));

	////////////
	// Set Control Word
	////////////
    struct FPUControlWord cw;
	memset(&cw, 0, sizeof(struct FPUControlWord));
	/////////////////////
	// Exceptions Masks //
	/////////////////////
	// Invalid Operation (InvOp), Divide By Zero (DivZero), Overflow (Overflow), Underflow (Underflow), Precision
	cw.InvalidOperand = 1;
	cw.DenormalOperand = 1;
	cw.ZeroDevide = 1;
	cw.Overflow = 1;
	cw.Underflow = 1;
	cw.Precision = 1;
	///////////////////////
	//? Changed here?
	cw.PrecisionControl = 0b11;
	cw.RoundingControl = 0b00;
	cw.InfinityControl = 0;

	asm volatile("fldcw %0" :: "m"(cw));
	//  Check if FPU was enabled before calling this function
}