/**
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
MODULE_VERSION("0.1")



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