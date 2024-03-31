#include <console.h>
#include <fs/fat.h>
#include <hal/hal.h>
#include <drivers/keyboard.h>
#include <mm/memory.h>
#include <multiboot.h>
#include <fs/vfs.h>
#include <drivers/mouse.h>
#include <drivers/video.h>
#include <proc/sched.h>
#include "graphics.h"
#include "terminal.h"
#include "yutani.h"

static yutani_t * yctx;
static yutani_window_t * window = NULL;
static char * title_str;


int kmain(multiboot_info_t *info) {
    
    video_init(25, 80);
    clear();
    
    pmm_init(info->mem_high + info->mem_low, (uint32_t *) info->mmap_addr, info->mmap_len);
    vmm_init();
    kheap_init();
    
    vbe_init(info);
    
    hal_init();
    
    // keyboard_init();
    mouse_init();
    
    syscall_init();
    install_tss();
    
    vfs_init();
    floppy_init();
    ata_init();
    
    sched_init();


	yutani_window_advertise_icon(yctx, window, title_str, "star");


    
    while(1)
        halt();
    
    return 0;
}