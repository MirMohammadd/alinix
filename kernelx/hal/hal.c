
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
 * @file hal.c

 */
#include <hal/hal.h>

void hal_init() {
    disable_int();
    gdt_init();
    idt_init(0x8);
    pic_init(0x20, 0x28);
    pit_init();
    pit_start_counter(100, PIT_COUNTER_0, PIT_MODE_SQUAREWAVEGEN);
    enable_int();
}

void sleep(int s) {
    // TODO better solution
    int ticks = get_tick_count() + s;
    int passed = 0;
    while((passed += get_tick_count()) < ticks);
}

void reboot() {
    outportb(0x64, 0xFE);
}