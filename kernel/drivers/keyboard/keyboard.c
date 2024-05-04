#include <alinix/kernel.h>
#include <alinix/keyboard.h>
#include <alinix/port.h>
#include <alinix/isr.h>


void clear_screen() {
    asm("call clear_screen");
}

void init_keyboard() {
    asm("call init_keyboard");
}

void wait_for_key_press() {
    asm("call wait_for_key_press");
}

void read_scan_code() {
    asm("call read_scan_code");
}

void print_scan_code() {
    asm("call print_scan_code");
}

