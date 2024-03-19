/*
 * Copyright (c) 2024 Heisenberg. All rights reserved.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO, THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define lidt(idt) asm("lidt "#idt)
#define lgdt(gdt) asm("lgdt "#gdt)
#define iret()                                  \
    asm("add esp, 0x4");                        \
    asm("leave");                               \
    asm("pop eax");                             \
    asm("iret")

#define set_es(var)                             \
    asm("mov edx, "#var"\n\t"                   \
        "mov es, dx" :: "r"(var))

#define set_cs(var)                             \
    asm("mov edx, "#var"\n\t"                   \
        "mov cs, dx")

#define set_ds(var)                             \
    asm("mov edx, "#var"\n\t"                   \
        "mov ds, dx")

#define set_ss(var)                             \
    asm("mov edx, "#var"\n\t"                   \
        "mov ss, dx")

#define set_gs(var)                             \
    asm("mov edx, "#var"\n\t"                   \
        "mov gs, dx")

#define write_mem_es(offset, value)             \
    asm("mov edx, "#value"\n\t"                 \
        "mov word [es:"#offset"], edx")         \

#define ltr(gdt_index)                          \
    asm("mov edx, "#gdt_index"\n\t"             \
        "ltr dx")
