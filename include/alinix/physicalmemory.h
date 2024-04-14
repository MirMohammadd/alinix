#ifndef __ALINIX_KERNEL_PHYISCAL_MEMORY_H
#define __ALINIX_KERNEL_PHYISCAL_MEMORY_H

#include <alinix/types.h>

#define BLOCK_SIZE 4_KB
#define BLOCKS_PER_BYTE 8 //Every byte describes 8 blocks

typedef struct multiboot_memory_map {
    unsigned int size;
    unsigned long base_addr_low;
    unsigned long base_addr_high;
    unsigned long length_low;
    unsigned long length_high;
    unsigned int type;
}  __attribute__((packed)) grub_multiboot_memory_map_t;

#endif