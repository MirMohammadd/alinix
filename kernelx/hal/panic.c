#include <console.h>
#include <drivers/audio.h>
#include <drivers/io.h>
#include <drivers/video.h>
#include <panic.h>

void panic() {
    disable_int();
    beep(1);
    console_print("\nPANIC");
    draw_rect(400, 300, 200, 200, 0x000000);
    while(1);
}