/**
 * @author Ali Mirmohammad
 * @file rate.c
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
 *  - Simple Driver rate for p/s 2 mouse driver.
 */



#include <alinix/types.h>
#include <alinix/init.h>
#include <alinix/module.h>
#include <alinix/kernel.h>
#include <alinix/asm.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_LICENSE("AGPLv3")
MODULE_DESCRIPTION("Simple Driver rate for p/s 2 mouse driver.")
MODULE_VERSION("1.0")


/**
 * @brief Sets the rate of a PS/2 mouse.
 *
 * This function sends a command to the PS/2 controller to address the mouse and 
 * sets the mouse sampling rate to a specified value (100 in this case). It waits 
 * for the controller's acknowledgment after each command.
 *
 * @note The function assumes that the `outb` and `inb` functions for port I/O 
 * are defined elsewhere in the codebase. Additionally, the `PAUSE` macro or 
 * function used for delaying must be defined or replaced with an appropriate 
 * delay function.
 */
static inline void rateOfDriver(void) {
    int ack;

    // Tell the controller to address the mouse
    outb(0xD4, 0x64);

    // Write the mouse command code to the controller's data port
    outb(0xF3, 0x60);

    // Wait until we can read back the acknowledge
    while (!(inb(0x64) & 1))
        PAUSE; // Replace with appropriate delay if necessary
    ack = inb(0x60); // Read back acknowledge. This should be 0xFA

    // Tell the controller to address the mouse again
    outb(0xD4, 0x64);

    // Write the parameter to the controller's data port
    outb(100, 0x60);

    // Wait until we can read back the acknowledge
    while (!(inb(0x64) & 1))
        PAUSE; // Replace with appropriate delay if necessary
    ack = inb(0x60); // Read back acknowledge. This should be 0xFA
}
