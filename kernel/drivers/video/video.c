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
#include <alinix/mm.h>
#include <alinix/memory.h>
#include <alinix/paging.h>

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

void __printk(char *buffer, ...){
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


void clear(){
    x = y = 0;
    for (int i = 0; i < vram.height;i++){
        *(vram.ram+i) = (uint16_t) 3872;
    }
}

// Start accessing the computer video hardware
void vbe_init(multiboot_info_t *info){
    vbe_controller_info_t *vbe_contr = (vbe_controller_info_t *) info->vbe_control_info;
    vbe_mode_info_t *vbe_mode = (vbe_mode_info_t *) info->vbe_mode_info;

    vbemem.buffer_size = vbe_mode->width * vbe_mode->height * (vbe_mode->bpp / 8);
    vbemem.mem = (uint32_t *) vbe_mode->framebuffer;
    vbemem.xres = vbe_mode->width;
    vbemem.yres = vbe_mode->height;
    vbemem.bpp = vbe_mode->bpp;
    vbemem.pitch = vbe_mode->pitch;

    if (!vbe_mode->framebuffer || vbe_contr->version <= 0x0200 || !(vbe_mode->attributes & 0x8)){
        if(vbe_mode->width != 80 && vbe_mode->height != 25) {
            regs16_t regs;
            regs.ax = 0x3;
            int32(0x10, &regs);
        }else{
            uint32_t addr = (uint32_t)vbe_mode->framebuffer;
            uint32_t addr_buf = addr + vbemem.buffer_size;
            vbemem.buffer = (uint32_t *) addr_buf;
            for(int i = 0; i < (int) vbemem.buffer_size / PAGE_SIZE; i++, addr += PAGE_SIZE, addr_buf += PAGE_SIZE) {
            vmm_map(get_kern_directory(), addr_buf, PAGE_PRESENT | PAGE_RW);
            vmm_map_phys(get_kern_directory(), addr, addr, PAGE_PRESENT | PAGE_RW);
        }
        windows_list_init();
        }
    }
}

void refresh_screen(){
    for (;;){
        pain
    }
}