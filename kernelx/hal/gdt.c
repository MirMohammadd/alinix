
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
 * @file gdt.c

 */
#include <hal/gdt.h>
#include <drivers/video.h>

#define GDT_LEN 8

struct gdt_info gdt_tab[GDT_LEN];
struct gdt_ptr ptr;

void gdt_init() {
    gdt_set_entry(0, 0, 0, 0);
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A);
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92);
    gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA);
    gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2);
    
    ptr.base = (uint32_t) &gdt_tab;
    ptr.limit = (sizeof(struct gdt_info) * GDT_LEN) - 1;
    
    gdt_set(&ptr);
}

void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access) {
    gdt_tab[index].base_low = base & 0xFFFF;
    gdt_tab[index].base_middle = (base >> 16) & 0xFF;
    gdt_tab[index].base_high = (base >> 24) & 0xFF;
    gdt_tab[index].limit_low = limit & 0xFFFF;
    gdt_tab[index].granularity = ((limit >> 16) & 0x0F) | (0xCF & 0xF0);
    gdt_tab[index].flags = access;
}