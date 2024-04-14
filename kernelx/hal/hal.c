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