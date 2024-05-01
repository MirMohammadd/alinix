#ifndef __ALINIX_KERNEL_ML_BOOT_H
#define __ALINIX_KERNEL_ML_BOOT_H


#include <alinix/types.h>

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_BOOTLOADER MAGIC 0x2BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00000003





typedef struct multiboot_info_header{
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
    uint32_t entry_addr;
    uint32_t mode_type;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
}__attribute__((__packed__)) multiboot_header_t;





#include <alinix/physicalmemory.h>


#endif // 