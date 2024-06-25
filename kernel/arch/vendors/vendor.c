/**
 * @author Ali Mirmohammad
 * @file vendor.c
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
 * @abstract:
 *  - Vendor ID implementation.
*/

#include <alinix/types.h>
#include <alinix/vendors.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Vendor ID implementation")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

/**
 * Retrieves CPU information using the CPUID instruction.
 *
 * This function uses the CPUID instruction to retrieve information about the CPU. It takes a
 * `code` parameter that specifies the type of information to retrieve, and pointers to `a` and `d`
 * variables that will store the resulting information. The CPUID instruction writes the information
 * to the `a` and `d` registers, so this function uses inline assembly to read those registers and
 * store the information in the provided variables.
 *
 * @param code The CPUID code that specifies the type of information to retrieve.
 * @param a A pointer to a uint32_t variable to store the resulting information in the `a` register.
 * @param d A pointer to a uint32_t variable to store the resulting information in the `d` register.
 *
 * @throws None
 */
static inline void cpuid(int code, uint32_t *a, uint32_t *d) {
  asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}
 
/** issue a complete request, storing general registers output as a string
 */
static inline int cpuid_string(int code, uint32_t where[4]) {
  asm volatile("cpuid":"=a"(*where),"=b"(*(where+1)),
               "=c"(*(where+2)),"=d"(*(where+3)):"a"(code));
  return (int)where[0];
}