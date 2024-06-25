/**
 * @author Ali Mirmohammad
 * @file idt.c
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

/**
 * @abstraction:
 *  - Provides util for IDT functionality.
*/

#include <alinix/idt.h>
#include <alinix/memory.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("IDT utility functions")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")




struct IDTEntry idtEntries[IDT_ENTRY_SIZE];
struct IDTPointer idtPointer;


/**
 * Sets the descriptor for an Interrupt Descriptor Table (IDT) entry.
 *
 * @param number      The index of the IDT entry to be set.
 * @param handler     A pointer to the interrupt handler function.
 * @param accesLevel  The access level of the IDT entry.
 */
IdtSetDescriptor(uint32_t number, void (*handler)(), int accesLevel){
    uint32_t callerBase = (uint32_t)handler;
    idtEntries[number].handlerLowBits = (uint16_t)(callerBase & 0xFFFF);
    idtEntries[number].handlerHighBits = (uint16_t)((callerBase >> 16) & 0xFFFF);
    idtEntries[number].reserved = 0;
    idtEntries[number].access = IDT_PRESENT | ((accesLevel & 3) << 5) | IDT_INTERRUPT;
    idtEntries[number].selector = 0x8;
}


/**
 * Installs the Interrupt Descriptor Table (IDT) with default exception and interrupt handlers.
 * Also remaps the Programmable Interrupt Controllers (PIC) for proper interrupt handling.
 */
void Install(){
        idtPointer.size = sizeof(struct IDTEntry) * IDT_ENTRY_SIZE - 1;
    idtPointer.base = (uint32_t)&idtEntries[0];

    memset((void*)&idtEntries[0], 0, sizeof(struct IDTEntry) * IDT_ENTRY_SIZE - 1);

    for(int i = 0; i < IDT_ENTRY_SIZE; i++)
        IdtSetDescriptor(i, IgnoreInterrupt,1);

    IdtSetDescriptor(0x00, HandleException0x00,1);
    IdtSetDescriptor(0x01, HandleException0x01,1);
    IdtSetDescriptor(0x02, HandleException0x02,1);
    IdtSetDescriptor(0x03, HandleException0x03,1);
    IdtSetDescriptor(0x04, HandleException0x04,1);
    IdtSetDescriptor(0x05, HandleException0x05,1);
    IdtSetDescriptor(0x06, HandleException0x06,1);
    IdtSetDescriptor(0x07, HandleException0x07,1);
    IdtSetDescriptor(0x08, HandleException0x08,1);
    IdtSetDescriptor(0x09, HandleException0x09,1);
    IdtSetDescriptor(0x0A, HandleException0x0A,1);
    IdtSetDescriptor(0x0B, HandleException0x0B,1);
    IdtSetDescriptor(0x0C, HandleException0x0C,1);
    IdtSetDescriptor(0x0D, HandleException0x0D,1);
    IdtSetDescriptor(0x0E, HandleException0x0E,1);
    IdtSetDescriptor(0x0F, HandleException0x0F,1);
    IdtSetDescriptor(0x10, HandleException0x10,1);
    IdtSetDescriptor(0x11, HandleException0x11,1);
    IdtSetDescriptor(0x12, HandleException0x12,1);
    IdtSetDescriptor(0x13, HandleException0x13,1);

    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x00, HandleInterruptRequest0x00,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x01, HandleInterruptRequest0x01,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x02, HandleInterruptRequest0x02,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x03, HandleInterruptRequest0x03,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x04, HandleInterruptRequest0x04,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x05, HandleInterruptRequest0x05,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x06, HandleInterruptRequest0x06,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x07, HandleInterruptRequest0x07,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x08, HandleInterruptRequest0x08,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x09, HandleInterruptRequest0x09,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x0A, HandleInterruptRequest0x0A,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x0B, HandleInterruptRequest0x0B,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x0C, HandleInterruptRequest0x0C,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x0D, HandleInterruptRequest0x0D,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x0E, HandleInterruptRequest0x0E,1);
    IdtSetDescriptor(IDT_INTERRUPT_OFFSET + 0x0F, HandleInterruptRequest0x0F,1);

    IdtSetDescriptor((IDT_INTERRUPT_OFFSET + 0xDD), HandleInterruptRequest0xDD,1);
    IdtSetDescriptor(0x80, HandleInterruptRequest0x60, 3);

    // Remap the PIC
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);

    // remap
    outportb(0x21, IDT_INTERRUPT_OFFSET);
    outportb(0xA1, IDT_INTERRUPT_OFFSET+8);

    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);

    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);

    outportb(0x21, 0x00);
    outportb(0xA1, 0x00);

    asm volatile("lidt %0" : : "m" (idtPointer));
}

/**
 * Enables interrupts by setting the Interrupt Flag (IF) in the EFLAGS register.
 */
void EnableInterrupts()
{
    asm volatile ("sti");
}
/**
 * Disables interrupts by clearing the Interrupt Flag (IF) in the EFLAGS register.
 */
void DisableInterrupts()
{
    asm volatile ("cli");
}

/**
 * Checks if interrupts are enabled by reading the Interrupt Flag (IF) in the EFLAGS register.
 *
 * @return true if interrupts are enabled, false otherwise.
 */
bool AreEnabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}