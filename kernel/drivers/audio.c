#include <drivers/audio.h>
#include <drivers/io.h>

void beep() {
    outportb(0xB6, 0x43);
    outportb(30, 0x42);
    outportb(5, 0x42);
    
    outportb(inportb(0x61) | 3, 0x61);
}