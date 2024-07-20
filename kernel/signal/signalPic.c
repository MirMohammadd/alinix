/**
 * @author Ali Mirmohammad
 * @file signalPic.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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

#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/module.h>
#include <alinix/asm.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Signal Picture")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

#define PIC_EOI		0x20		/* End-of-interrupt command code */


VOID PIC_sendEOI(uint8_t irq){
    if (irq >= 8)
        outportb(PIC2_COMMAND,PIC_EOI);
    outb(PIC1_COMMAND,PIC_EOI);
}