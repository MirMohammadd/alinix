#include <alinix/kernel.h>
#include <alinix/asm/console.h>


void srm_printk(const char* str)
{
    // VGA text mode buffer
    volatile char* video_memory = (volatile char*)0xb8000;
    for(int i = 0; str[i] != '\0'; ++i)
    {
        // Each character takes 2 bytes: ASCII and attribute
        video_memory[i*2] = str[i];
        video_memory[i*2+1] = 0x0F; // White text on black background
    }
}
