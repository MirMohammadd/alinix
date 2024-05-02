#include <alinix/idt.h>
#include <alinix/types.h>

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