/**
 * @author Ali Mirmohammad
 * @file lock.c
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
 *  - Locks the kernel.
*/
#include <alinix/lock.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Locks the kernel/ kernel threads.")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.2")

/**
 * @brief Pause the CPU to reduce contention.
 *
 * This function pauses the CPU to reduce contention in a multi-threaded environment.
 * It uses the `pause` assembly instruction to temporarily stop the CPU from executing
 * instructions until the contention is resolved.
 *
 * @note This function is typically used in locking mechanisms to reduce the chances
 *       of race conditions.
 */
void Lock(){
    asm ("pause");
}