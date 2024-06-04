/**
 * @author Ali Mirmohammad
 * @file tss.c
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
 *  - Provide util over TSS.
*/

#include <alinix/core/tss.h>
#include <alinix/tss.h>
#include <alinix/enums.h>
#include <alinix/memory.h>
#include <alinix/gdt.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("TSS abstraction")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


static struct TSSEntry tss;

/**
 * Install a Task State Segment (TSS) entry.
 *
 * This function installs a TSS entry in the Global Descriptor Table (GDT) and initializes it with the provided parameters.
 * It performs the following steps:
 *
 * 1. Clears the `tss` structure using `memset`.
 * 2. Calculates the base address of the `tss` structure.
 * 3. Calls `GGetDescriptor` to retrieve the descriptor for the TSS entry from the GDT.
 * 4. Initializes the `tss` structure with the provided `kernelSS` and `kernelESP` values.
 * 5. Sets the `iomap` field of the `tss` structure to the size of the `struct TSSEntry`.
 * 6. Calls `flush_tss` to invalidate the TSS cache.
 *
 * @param idx The index of the TSS entry in the GDT.
 * @param kernelSS The value to set for the `ss0` field of the TSS.
 * @param kernelESP The value to set for the `esp0` field of the TSS.
 *
 * @return void
 */
void TSS_Install(uint32_t idx, uint32_t kernelSS, uint32_t kernelESP){
    memset(&tss,0,sizeof(struct TSSEntry));

    uint32_t base = (uint32_t)&tss;

    GGetDescriptor(idx, base, base + sizeof (struct TSSEntry), 0xE9, 0);

    /////////////
    // Init TSS
    memset ((void*) &tss, 0, sizeof (struct TSSEntry));

    tss.ss0 = kernelSS;
	tss.esp0 = kernelESP;
	tss.iomap = sizeof(struct TSSEntry);

    flush_tss();


}

/**
 * Set the stack pointer and stack base address in the Task State Segment (TSS).
 *
 * This function sets the stack pointer and stack base address in the TSS.
 * It performs the following steps:
 *
 * 1. Sets the `ss0` field of the TSS to the provided `kernelSS` value.
 * 2. Sets the `esp0` field of the TSS to the provided `kernelESP` value.
 *
 * @param kernelSS The value to set for the `ss0` field of the TSS.
 * @param kernelESP The value to set for the `esp0` field of the TSS.
 *
 * @return void
 */
void TSS_SetStack(uint32_t kernelSS, uint32_t kernelESP){
    tss.ss0 = kernelSS;
    tss.esp0 = kernelESP;
}

/**
 * Get the current Task State Segment (TSS).
 *
 * This function returns a pointer to the current TSS.
 *
 * @return A pointer to the current TSS.
 */
struct TSSEntry* TSS_GetCurrent(){
    return &tss;
}