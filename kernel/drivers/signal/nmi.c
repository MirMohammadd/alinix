/**
 * @author Ali Mirmohammad
 * @file nmi.c
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
 *  - Implements the NMI signal.
*/

#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/port.h>
#include <alinix/types.h>
#include <alinix/nmi.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("NMI signal")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")


/**
 * @brief Function that enables the NMI
*/
VOID NMI_enable(){
    outportb(NMI_PORT,inportb(NMI_PORT) & 0x7F);
    inportb(0x71);
}

/**
 * @brief Function that disables the NMI
*/

VOID NMI_disable(){
    outportb(NMI_PORT, inportb(NMI_PORT) | 0x80);
    inportb(0x71);
}
