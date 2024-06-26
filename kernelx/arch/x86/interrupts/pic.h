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

#ifndef _PIC_H_
#define _PIC_H_

#include <lib/types.h>
#include "irq.h"



#define ICW1_INIT 0x10
#define ICW4_8086 0x01
#define OCW2_EOI 0x20 /*Set the mode of PIC controllers*/
#define OCW3_READ_ISR 0x0b
#define OCW3_READ_IRR 0x0a /*define a value for the  read irr command register*/
#define EOI 0x20 /*End if interrupt command*/


/**
 * @file pic.h Programmable Interruptr Controller
 * @date 2010
 * @license MIT License
 *
 * PIC's functions
 * Only used byinterrupt.c
 *
 * @see Intel 8259A datasheet
 */

/** Setup PIC and Disable all IRQ lines */
void x86_pic_setup(void);

void x86_pic_enable_irq_line(uint32_t numirq);

void x86_pic_disable_irq_line(uint32_t numirq);

#endif
