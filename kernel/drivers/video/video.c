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
#include <alinix/video.h>
#include <alinix/gui/window.h>
#include <alinix/types.h>
#include <alinix/kernel.h>


static int x;
static int y;
struct video_mem vram;
struct vbe_mem vbemem;


#define PRINT_K_BUFFER_SIZE 256

void video_init(int h,int w){
    x = 0;
    y = 0;
    vram.height = h;
    vram.width = w;
    vram.ram = (uint16_t *) 0xB8000; // Settle the RAM
}
void check() {
    if(x >= vram.width) {
        x = 0;
        y++;
    }
    if(y >= vram.height) {
        y--;
        scroll();
    }
}

void scroll() {
    for(int i = 0; i < vram.width * (vram.height - 1); i++) {
        vram.ram[i] = vram.ram[i + vram.width];
    }
    for(int i = 0; i < vram.width; i++) {
        vram.ram[vram.width * (vram.height - 1) + i] = 3872;
    }
}

void printk(char *buffer, ...){
    char str[PRINT_K_BUFFER_SIZE];
    va_list args;
    va_start(args,buffer);
    print(str, buffer, args);
    va_end(args);
    printk_string(str);
}

void printk_string(char *buffer){
    int i = 0;

    check();

    while (buffer[i] != '\0'){
        switch(buffer[i]){
            case '\0':
                return;
            case '\b':
                vram.ram[(y * vram.width) + --x] = (uint16_t)3872;
                i++;
                break;
            case '\n':
                i++;
                y++;
                x = 0;
                check();
                break;
            
            case '\r':
                i++;
                x = 0;
                break;
            default:
                check();
                vram.ram[(y * vram.width) + x++] = (uint16_t) (3840 | buffer[i++]);
                break;
        }
    }
}
