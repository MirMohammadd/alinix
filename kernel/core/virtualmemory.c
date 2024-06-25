/**
 * @author Ali Mirmohammad
 * @file virtualmemory.c
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
 *  - Util for V memory.
*/
#include <alinix/virtualmemory.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Virtual Memory")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")



/**
 * Map a virtual address to a physical address in the page table.
 *
 * This function maps a virtual address to a physical address in the page table. It performs the following steps:
 *
 * 1. Retrieves the page table entry for the virtual address using the `GetPageForAddress` function.
 * 2. Sets the frame field of the page table entry to the physical address divided by the page size.
 * 3. Sets the isUser field of the page table entry based on the value of the `kernel` parameter.
 * 4. Sets the readWrite field of the page table entry based on the value of the `writeable` parameter.
 * 5. Sets the present field of the page table entry to 1.
 * 6. Invalidates the TLB entry for the virtual address using the `invlpg` function.
 *
 * @param physAddress The physical address to map.
 * @param virtAddress The virtual address to map.
 * @param kernel Indicates whether the mapping is for the kernel or user space.
 * @param writeable Indicates whether the mapping is writeable.
 *
 * @return void
 */
mapVirtualToPhysical(void* physAddress, void* virtAddress, bool kernel, bool writeable)
{
    struct PageTableEntry* page = GetPageForAddress((uint32_t)virtAddress, true, writeable, !kernel);

    page->frame = (uint32_t)physAddress / PAGE_SIZE;
    page->isUser = kernel ? 0 : 1;
    page->readWrite = writeable ? 1 : 0;
    page->present = 1;

    invlpg(virtAddress);
}
void* GetPageForAddress(uint32_t virtualAddress, bool shouldCreate, bool readWrite, bool userPages)
{

}