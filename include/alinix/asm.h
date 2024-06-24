/**
 * @author Ali Mirmohammad
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
 * @file asm.h
 * @abstraction:
 *  - Kernel ASM implemented.
*/
#ifndef __ALINIX_KERNEL_ASM_H
#define __ALINIX_KERNEL_ASM_H

# define RET    bx      lr

/**
 * @brief outing the data to specific port.
*/
#define outb(_port, _data)  \
    asm volatile("outb %b0, %w1" \
        : \
        : "a" (_data), "Nd" (_port) \
    );

#define PAUSE asm("pause")

#endif /*__ALINIX_KERNEL_ASM_H*/