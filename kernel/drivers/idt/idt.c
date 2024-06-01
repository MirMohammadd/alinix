/**
 * @author Ali Mirmohammad
 * @file idt.c
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
 * 	- IDT implementing here.
*/
#include <alinix/idt.h>
#include <alinix/types.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("IDT implementation module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


struct idt_ptr idtr;
struct idt_info idt[MAX_INTERRUPTS];

void install_ir(uint32_t i, uint16_t flags, uint16_t sel, void *irq) {
    uint32_t ir_addr = (uint32_t) irq;
    
    idt[i].base_low = (uint16_t) ir_addr & 0xFFFF;
	idt[i].base_high = (uint16_t) (ir_addr >> 16) & 0xFFFF;
	idt[i].reserved = 0;
	idt[i].flags = (uint8_t) flags;
	idt[i].sel = sel;
}