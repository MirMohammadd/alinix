/**
 * @author Ali Mirmohammad
 * @file initSig.c
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


#include <alinix/kernel.h>
#include <alinix/types.h>
#include <alinix/init.h>
#include <alinix/module.h>
#include <alinix/asm.h>


#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */




MODULE_AUTHOR("ali Mirmohammad")
MODULE_DESCRIPTION("initSig")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0.0")



/**
 * @brief Remap the PIC with new vector offsets.
 *
 * This function initializes the PIC in cascade mode and remaps
 * the interrupt vectors for the master and slave PICs. The original
 * interrupt masks are saved and restored after the remapping.
 *
 * @param offset1 The new interrupt vector offset for the master PIC
 * @param offset2 The new interrupt vector offset for the slave PIC
 */
void PIC_remap(int offset1, int offset2)
{
	uint8_t a1, a2;
	
	a1 = inportb(PIC1_DATA);                        // save masks
	a2 = inportb(PIC2_DATA);
	
	outportb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	outportb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	outportb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	outportb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	outportb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outportb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	
	outportb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	outportb(PIC2_DATA, ICW4_8086);
	
	outportb(PIC1_DATA, a1);   // restore saved masks.
	outportb(PIC2_DATA, a2);
}