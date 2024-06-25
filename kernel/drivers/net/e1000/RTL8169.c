/**
 * @author Ali Mirmohammad
 * @file RTL8169.c
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
 *  - Kernel RTL driver.
*/
#include <net/RTL8169.h>
#include <alinix/init.h>
#include <alinix/kernel.h>
#include <alinix/port.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("RTL8169 Kernel RTL Driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")


/**
 * @brief Get the mac address of the device using I/O ports.
*/
/**
 * Retrieves the MAC address of the network interface card (NIC) and stores it in the provided array.
 *
 * @param macAddress An array of 6 integers to store the MAC address.
 *
 * @return None.
 *
 * @throws None.
 *
 * @details
 * This function retrieves the MAC address of the network interface card (NIC) by reading the MAC
 * address from the I/O port address specified by the `ioaddr` variable. It assumes that the
 * `ioaddr` variable is defined and contains the I/O port address of the NIC.
 *
 * The function reads 6 bytes from the I/O port address and stores them in the `macAddress` array.
 * Each byte represents a part of the MAC address.
 *
 * After reading the MAC address, the function sets the Reset bit (0x10) in the Command Register
 * (0x37) of the NIC to reset it. It waits until the Reset bit is cleared in the Command Register
 * before returning.
 *
 * @note
 * This function assumes that the `inportb` and `outportb` functions are defined to read from
 * and write to I/O ports, respectively.
 */
void getMacAddr(int macAddress[]){
    char i;
    for (i = 0;i < 6;i++){
        macAddress[i] = inportb(ioaddr + 1);
    }
     outportb(ioaddr + 0x37, 0x10); /*set the Reset bit (0x10) to the Command Register (0x37)*/
    while(inportb(ioaddr + 0x37) & 0x10);
}