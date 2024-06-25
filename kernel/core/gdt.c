/**
 * @author Ali Mirmohammad
 * @file gdt.c
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
 *  - Global descriptor table utils.
 *  - Define memory access util.
*/
#include <alinix/gdt.h>
#include <alinix/types.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Global Descriptor Table utils")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")



struct GDTEntry gdtEntries[6];
struct GDTPointer gdtPointer;

/**
 * @brief Set the descriptor in the Global Descriptor Table (GDT).
 *
 * This function sets the descriptor in the Global Descriptor Table (GDT) with
 * the specified number, base address, limit, access flags, and granularity.
 * The GDT is a data structure used by the x86 architecture to define the
 * characteristics of different memory segments.
 *
 * @param number The index of the descriptor in the GDT.
 * @param base The base address of the memory segment.
 * @param limit The limit address of the memory segment.
 * @param access The access flags for the memory segment.
 * @param gran The granularity flags for the memory segment.
 *
 * @warning This function must be called before using other functions in this module.
 *
 * @note The GDT is typically initialized once at boot time and then updated
 *       as needed.
 */
void GSetDescriptor(int number, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    /**
     * @brief Init the GDT here
     * @warning  You must call this function before using other functions in this module
    */
    gdtEntries[number].base_low    = (base & 0xFFFF);
    gdtEntries[number].base_middle = (base >> 16) & 0xFF;
    gdtEntries[number].base_high   = (base >> 24) & 0xFF;

    gdtEntries[number].limit_low   = (limit & 0xFFFF);
    gdtEntries[number].granularity = (limit >> 16) & 0x0F;

    gdtEntries[number].granularity |= gran & 0xF0;
    gdtEntries[number].access      = access;
}

/**
 * @brief Get the descriptor from the Global Descriptor Table (GDT).
 *
 * This function retrieves the descriptor at the specified index from the
 * Global Descriptor Table (GDT). The GDT is a data structure used by the x86
 * architecture to define the characteristics of different memory segments.
 *
 * @param number The index of the descriptor in the GDT.
 * @return A pointer to the GDTEntry structure representing the descriptor.
 *
 * @note The GDT is typically initialized once at boot time and then updated
 *       as needed.
 */
struct GDTEntry* GGetDescriptor(int number)
{
    return &gdtEntries[number];
}

/**
 * @brief Initialize the Global Descriptor Table (GDT).
 *
 * This function initializes the Global Descriptor Table (GDT) with the
 * appropriate descriptors for the kernel and user mode. It sets up the
 * null segment, code segment, data segment, user mode code segment, and
 * user mode data segment. The GDT is a data structure used by the x86
 * architecture to define the characteristics of different memory segments.
 *
 * @note The GDT is typically initialized once at boot time and then updated
 *       as needed.
 */
void GdtInit()
{
    gdtPointer.limit = (sizeof(struct GDTEntry) * 6) - 1;
    gdtPointer.base = (uint32_t)&gdtEntries;

    GdtSetDescriptor(0, 0, 0, 0, 0);                // Null segment
    GdtSetDescriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    GdtSetDescriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    GdtSetDescriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    GdtSetDescriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    // TSS descriptor will be loaded by the TSS class

    gdt_flush((uint32_t)&gdtPointer);
}

/**
 * @brief Set the descriptor in the Global Descriptor Table (GDT).
 *
 * This function sets the descriptor in the Global Descriptor Table (GDT) with
 * the specified number, base address, limit, access flags, and granularity.
 * The GDT is a data structure used by the x86 architecture to define the
 * characteristics of different memory segments.
 *
 * @param number The index of the descriptor in the GDT.
 * @param base The base address of the memory segment.
 * @param limit The limit address of the memory segment.
 * @param access The access flags for the memory segment.
 * @param gran The granularity flags for the memory segment.
 *
 * @note The GDT is typically initialized once at boot time and then updated
 *       as needed.
 */
void GdtSetDescriptor(int number, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdtEntries[number].base_low    = (base & 0xFFFF);
    gdtEntries[number].base_middle = (base >> 16) & 0xFF;
    gdtEntries[number].base_high   = (base >> 24) & 0xFF;

    gdtEntries[number].limit_low   = (limit & 0xFFFF);
    gdtEntries[number].granularity = (limit >> 16) & 0x0F;

    gdtEntries[number].granularity |= gran & 0xF0;
    gdtEntries[number].access      = access;
}