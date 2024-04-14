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