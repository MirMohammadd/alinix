#include <hal/hal.h>
#include <hal/tss.h>
#include <lib/string.h>
#include <drivers/video.h>

static tss_t tss;

void flush_tss() {
    asm volatile("mov $0x2B, %ax; \
                  ltr %ax;");
}

void install_tss() {
    uint32_t base = (uint32_t) &tss;
    gdt_set_entry(5, base, base + sizeof(tss_t), 0xE9);
    memset((void *) base, 0, sizeof(tss_t));

    tss.esp0 = 0;
    tss.ss0 = 0x10;
    tss.cs = 0x0B;
    tss.ss = 0x13;
    tss.es = 0x13;
    tss.ds = 0x13;
    tss.fs = 0x13;
    tss.gs = 0x13;
    
    flush_tss();
}

void set_esp0(uint32_t esp) {
    tss.esp0 = esp;
}