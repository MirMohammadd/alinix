
/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg
 * @file idt.h

 */

#ifndef IDT_H
#define IDT_H


#include <types.h>


#define MAX_INTERRUPTS 256


struct idt_info{
    uint16_t base_low;
    uint16_t sel;
    uint8_t reserved;
    uint8_t flags;
    uint16_t base_high;
}__attribute__((__packed__));


struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((__packed__));

void idt_init(uint16_t code);
void default_ir_handler();
void install_ir(uint32_t i, uint16_t flags, uint16_t sel, void *irq);
extern void idt_set(struct idt_ptr *ptr);
extern void gen_int(uint32_t code);




#endif // IDT_H