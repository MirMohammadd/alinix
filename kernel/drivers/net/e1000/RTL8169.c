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
 * @abstraction:
 *  - Kernel RTL driver.
*/
#include <net/RTL8169.h>
#include <alinix/init.h>
#include <alinix/kernel.h>
#include <alinix/port.h>

void getMacAddr(int macAddress[]){
    char i;
    for (i = 0;i < 6;i++){
        macAddress[i] = inportb(ioaddr + 1);
    }
     outportb(ioaddr + 0x37, 0x10); /*set the Reset bit (0x10) to the Command Register (0x37)*/
    while(inportb(ioaddr + 0x37) & 0x10);
}