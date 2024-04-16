void flush_tss() {
    asm volatile("mov $0x2B, %ax; \
                  ltr %ax;");
}