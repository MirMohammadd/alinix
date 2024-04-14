#include <alinix/bootconsole.h>
#include <alinix/types.h>

static uint16_t* videoMemory = (uint16_t*)0xC00B8000;

void Scroll(){
    for (int i = 0; i < 24;i++){
        for (int m = 0; m < 80;m++){
            videoMemory[i * 80 + m] = videoMemory[(i + 1) * 80 + m];
        }
    }
    for (int x = 0;x<80;x++){
        uint16_t attrib = (BackgroundColor << 4) | (ForegroundColor & 0x0F);
        volatile uint16_t * where;
        where = (volatile uint16_t *)videoMemory + (24 * VGA_WIDTH + x) ;
        *where = ' ' | (attrib << 8);
    }
}