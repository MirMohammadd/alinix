/**
 * @author Ali Mirmohammad
 * @file printk.c
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
 *  - Provides util over printk for printing the kernel info.
 *  - Note: May be obsolete soon.
*/
#include <alinix/printk.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Printk utility")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

/**
 * Print a given data buffer to the console.
 *
 * This function prints a given data buffer to the console based on the current screen mode and initialization status.
 * It performs the following steps:
 *
 * 1. If the screen mode is set to TextMode, iterate over each character in the data buffer and call the `Write` function to write it to the console.
 * 2. If the console is initialized and GDB is not enabled, iterate over each character in the data buffer and call the `Write` function to write it to the console.
 *
 * @param data The data buffer to be printed.
 * @param length The length of the data buffer.
 *
 * @return None.
 *
 * @throws None.
 */
void Print(const char* data, uint32_t length) {
    /* Send data through serial port */
    if(screenMode == TextMode)
    {
        for (uint32_t i = 0; i < length; i++)
            Write(data[i]);
    }
    else if(Initialized && (gdbEnabled == false))
    {
        for (uint32_t i = 0; i < length; i++)
            Write(data[i]);
    }
}