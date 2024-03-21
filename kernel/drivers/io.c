#include <drivers/io.h>

uint8_t inportb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %%dx, %%al" : "=a" (ret) : "d" (port));
    return ret;
}

uint16_t inportw(uint16_t port) {
    uint16_t ret;
    asm volatile("inw %%dx, %%ax" : "=a" (ret) : "d" (port));
    return ret;
}

void outportb(uint16_t port, uint8_t val) {
    asm volatile("outb %%al, %%dx" : : "d" (port), "a" (val));
}

void halt() {
    asm volatile("hlt");
}

void enable_int() {
    asm volatile("sti");
}

void disable_int() {
    asm volatile("cli");
}