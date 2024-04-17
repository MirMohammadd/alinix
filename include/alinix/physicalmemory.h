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

#ifndef __ALINIX_KERNEL_PHYISCAL_MEMORY_H
#define __ALINIX_KERNEL_PHYISCAL_MEMORY_H

#include <alinix/types.h>

#define BLOCK_SIZE 4_KB
#define BLOCKS_PER_BYTE 8 //Every byte describes 8 blocks

#define	TAILQ_REMOVE(head, elm, field) do {				\
	if (((elm)->field.tqe_next) != NULL)				\
		(elm)->field.tqe_next->field.tqe_prev = 		\
		    (elm)->field.tqe_prev;				\
	else								\
		(head)->tqh_last = (elm)->field.tqe_prev;		\
	*(elm)->field.tqe_prev = (elm)->field.tqe_next;			\
} while (/*CONSTCOND*/0)

typedef struct multiboot_memory_map {
    unsigned int size;
    unsigned long base_addr_low;
    unsigned long base_addr_high;
    unsigned long length_low;
    unsigned long length_high;
    unsigned int type;
}  __attribute__((packed)) grub_multiboot_memory_map_t;

typedef struct {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
} multiboot_info_t;

static uint32_t memorySize;
static uint32_t usedBlocks;
static uint32_t maximumBlocks;
static uint32_t* memoryArray;

static inline void SetBit(uint32_t bit) {
    memoryArray[bit / 32] |= (1 << (bit % 32));
}

static inline void UnsetBit(uint32_t bit) {
    memoryArray[bit / 32] &= ~(1 << (bit % 32));
}

static inline bool TestBit(uint32_t bit) {
    return memoryArray[bit / 32] & (1 << (bit % 32));
}

static uint32_t FirstFree();
static uint32_t FirstFreeSize(uint32_t size);

static void Initialize(uint32_t size, uint32_t bitmap) {
    memorySize = size;
    maximumBlocks = size / 4096;
    memoryArray = (uint32_t*)bitmap;
}

static void SetRegionFree(uint32_t base, uint32_t size) {
    uint32_t start = base / 4096;
    uint32_t end = (base + size) / 4096;
    for (uint32_t i = start; i < end; i++) {
        UnsetBit(i);
    }
}

static void SetRegionUsed(uint32_t base, uint32_t size) {
    uint32_t start = base / 4096;
    uint32_t end = (base + size) / 4096;
    for (uint32_t i = start; i < end; i++) {
        SetBit(i);
    }
}

static void ParseMemoryMap(const multiboot_info_t* mbi) {
    uint32_t mmap_addr = mbi->mmap_addr;
    uint32_t mmap_length = mbi->mmap_length;
    while (mmap_length > 0) {
        uint32_t base = *(uint32_t*)mmap_addr;
        uint32_t length = *(uint32_t*)(mmap_addr + 8);
        uint32_t type = *(uint32_t*)(mmap_addr + 16);
        if (type == 1) {
            SetRegionUsed(base, length);
        } else {
            SetRegionFree(base, length);
        }
        mmap_addr += 24;
        mmap_length -= 24;
    }
}

static void* AllocateBlock() {
    uint32_t free = FirstFree();
    if (free == (uint32_t)-1) {
        return NULL;
    }
    SetBit(free);
    usedBlocks++;
    return (void*)(free * 4096);
}

static void FreeBlock(void* ptr) {
    uint32_t address = (uint32_t)ptr;
    uint32_t block = address / 4096;
    UnsetBit(block);
    usedBlocks--;
}

static void* AllocateBlocks(uint32_t size) {
    uint32_t free = FirstFreeSize(size);
    if (free == (uint32_t)-1) {
        return NULL;
    }
    uint32_t start = free;
    uint32_t end = free + (size / 4096);
    for (uint32_t i = start; i < end; i++) {
        SetBit(i);
    }
    usedBlocks += (size / 4096);
    return (void*)(start * 4096);
}

static void FreeBlocks(void* ptr, uint32_t size) {
    uint32_t address = (uint32_t)ptr;
    uint32_t start = address / 4096;
    uint32_t end = start + (size / 4096);
    for (uint32_t i = start; i < end; i++) {
        UnsetBit(i);
    }
    usedBlocks -= (size / 4096);
}

static uint32_t AmountOfMemory() {
    return memorySize;
}

static uint32_t UsedBlocks() {
    return usedBlocks;
}

static uint32_t FreeBlocks() {
    return maximumBlocks - usedBlocks;
}

static uint32_t TotalBlocks() {
    return maximumBlocks;
}

static uint32_t GetBitmapSize() {
    return maximumBlocks / 32;
}

static uint32_t pageRoundUp(uint32_t address) {
    return (address + 4095) & ~4095;
}

static uint32_t pageRoundDown(uint32_t address) {
    return address & ~4095;
}

#endif