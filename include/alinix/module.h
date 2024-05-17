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

inline uint32_t cpu_to_le32(uint16_t value) {
    #if defined(__GNUC__) || defined(__clang__)
        return __builtin_bswap32(value);
    #else
        return ((value & 0xFF) << 24) |
               ((value & 0xFF00) << 8) |
               ((value & 0xFF0000) >> 8) |
               ((value & 0xFF000000) >> 24);
    #endif
}
#define MMIO32(addr) (*(volatile uint32_t *)(addr))

// Read a double-word (32-bit) value from a MMIO register with an offset
inline uint32_t mmio_read_dword(uint32_t base_addr, uint32_t offset) {
    return MMIO32(base_addr + offset);
}

typedef struct mmio_s{
    volatile uint32_t* base;  // Base address of the MMIO region
    size_t size; // Size of the MMIO region in bytes
    volatile uint32_t *addr;               
} mmio_region_t;



#endif