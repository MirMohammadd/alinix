/**
 * @author Ali Mirmohammad
 * @file 8042reset.c
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
 *  - Reset 8042 for kernel implemented.
*/
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/reboot.h>
#include <alinix/port.h>
#include <alinix/module.h>



MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Reset 8042 for kernel implemented.")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")




/**
 * Reboots the system using the x86 system call interface.
 *
 * This function calls the `DoSyscall()` function with specific arguments to initiate the reboot.
 * It uses the `__NR_reboot` system call number and the `LINUX_REBOOT_MAGIC1`, `LINUX_REBOOT_MAGIC2`,
 * `LINUX_REBOOT_CMD_POWER_OFF`, and `0` arguments to perform the reboot.
 *
 * @return void
 *
 * @throws None
 */
VOID reboot_x86_sys_call(){
    DoSyscall(__NR_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_POWER_OFF, 0, 0);
}


/**
 * Reboots the system.
 *
 * This function sends a reboot command to a specific port on the system's hardware.
 * It waits until the reboot command is accepted by checking the value of the `good` variable.
 * Once the reboot command is accepted, the function sends the reboot command to the port and then halts the system.
 *
 * @return void
 *
 * @throws None
 */
VOID reboot(){
    uint8_t good = 0x02;
    while (good & 0x2)
        good = (uint8_t)inportb(REBOOT_PORT);

    outportb(REBOOT_PORT,REBOOT_COMMAND);
    asm volatile("hlt");
}