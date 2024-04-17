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
#include <alinix/gdt.h>
#include <alinix/types.h>


struct GDTEntry gdtEntries[6];
struct GDTPointer gdtPointer;

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

struct GDTEntry* GGetDescriptor(int number)
{
    return &gdtEntries[number];
}

void GdtInit()
{
    gdtPointer.limit = (sizeof(struct GDTEntry) * 6) - 1;
    gdtPointer.base = (uint32_t)&gdtEntries;

    SetDescriptor(0, 0, 0, 0, 0);                // Null segment
    SetDescriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    SetDescriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    SetDescriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    SetDescriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    // TSS descriptor will be loaded by the TSS class

    gdt_flush((uint32_t)&gdtPointer);
}

void SetDescriptor(int number, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdtEntries[number].base_low    = (base & 0xFFFF);
    gdtEntries[number].base_middle = (base >> 16) & 0xFF;
    gdtEntries[number].base_high   = (base >> 24) & 0xFF;

    gdtEntries[number].limit_low   = (limit & 0xFFFF);
    gdtEntries[number].granularity = (limit >> 16) & 0x0F;

    gdtEntries[number].granularity |= gran & 0xF0;
    gdtEntries[number].access      = access;
}