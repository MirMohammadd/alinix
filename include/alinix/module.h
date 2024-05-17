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
 * @note:
 *  @reminder:
   ** Big-endian: Stores the most significant byte at the lowest memory address.
   ** Little-endian: Stores the least significant byte at the lowest memory address.
*/

#ifndef __ALINIX_KERNEL_MODULE_H
#define __ALINIX_KERNEL_MODULE_H

#include <alinix/types.h>
uint32_t le32_to_cpu(uint32_t le_value);

inline void mmio_write_dword(uint32_t addr, uint32_t value) {
    // Assuming 'addr' is the address of the MMIO register
    volatile uint32_t* reg = (volatile uint32_t*)addr;
    *reg = value;
}

#endif