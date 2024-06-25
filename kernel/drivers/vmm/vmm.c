/**
 * @author Ali Mirmohammad
 * @file vmm.c
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

/**
 * @abstraction:
 *  - kernel Memory drivers.
*/

#include <alinix/mm.h>
#include <alinix/paging.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel Memory Drivers")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")


#define RETURN_ADDR 0x400000
/*
 * |------------------------------------------------|
 * | 0x0 - 0x400000 -> identity mapped kernel space |
 * | kernel_end - 0x200000 -> kernel heap           |
 * | 0x200000 - 0x400000 -> paging structures       |
 * |------------------------------------------------|
 * | 0x400000 - 0x401000 -> common space            |
 * |------------------------------------------------|
 * | 0x401000 - 0x700000 -> free space              |
 * |------------------------------------------------|
 * | 0x700000 - 0x800000 -> elf loading space       |
 * |------------------------------------------------|
 * | 0x800000 - end -> programs address space       |
 * |------------------------------------------------|
 */

page_dir_t kern_dir[1024] __attribute__((aligned(4096)));
page_dir_t *current_dir = 0;

extern uint32_t kernel_start;
extern uint32_t kernel_end;



/**
 * Initializes the Virtual Memory Manager
 */
void vmm_init() {
    memset(kern_dir, 0, PAGEDIR_SIZE);
    memset((void *) get_page_table_bitmap(), 0, 0x10);
    map_kernel(kern_dir);
    change_page_directory(kern_dir);
    enable_paging();
}

/**
 * Maps the kernel in the given page directory
 */
void map_kernel(page_dir_t *pdir) {
    vmm_addr_t virt = 0x00000000;
    mm_addr_t phys = 0x0;
    
    // Identity map first 4MB
    for(int i = 0; i < 1024; i++, virt += PAGE_SIZE, phys += PAGE_SIZE) {
        if(pdir[virt >> 22] == 0) {
            if(!vmm_create_page_table(pdir, virt, PAGE_PRESENT | PAGE_RW)) {
                __printk("Error creating page table");
                return;
            }
        }
        ((uint32_t *) (pdir[virt >> 22] & ~0xFFF))[virt << 10 >> 10 >> 12] = phys | PAGE_PRESENT | PAGE_RW;
    }
    // Space for RETURN_ADDR
    uint32_t ret_addr = (uint32_t) RETURN_ADDR;
    if(!vmm_create_page_table(pdir, ret_addr, PAGE_PRESENT | PAGE_RW | PAGE_USER)) {
        __printk("Error creating page table");
        return;
    }
    ((uint32_t *) (pdir[ret_addr >> 22] & ~0xFFF))[ret_addr << 10 >> 10 >> 12] = ret_addr | PAGE_PRESENT | PAGE_RW | PAGE_USER;
}

/**
 * Switches page directory with the given one
 */
void change_page_directory(page_dir_t *p) {
    current_dir = p;
    load_pdbr((mm_addr_t) current_dir);
}

/**
 * Returns the current page directory.
 *
 * @return A pointer to the current page directory.
 *
 * @throws None
 */
page_dir_t *get_page_directory() {
    return current_dir;
}

/**
 * Returns the kernel page directory.
 *
 * @return A pointer to the kernel page directory.
 *
 * @throws None
 */
page_dir_t *get_kern_directory() {
    return kern_dir;
}

/**
 * Creates a page table for the given virtual address
 */
int vmm_create_page_table(page_dir_t *pdir, vmm_addr_t virt, uint32_t flags) {
    void *pt = page_table_malloc();
    if(!pt)
        return NULL;
    pdir[virt >> 22] = ((uint32_t) pt) | flags;
    return 1;
}

/**
 * Allocates a chunk of memory and maps it to the virtual address
 */
int vmm_map(page_dir_t *pdir, vmm_addr_t virt, uint32_t flags) {
    // Get a memory block
    mm_addr_t phys = (mm_addr_t) pmm_malloc();
    if(!phys) {
        __printk("VMM: Failed allocating memory \n");
        return NULL;
    }
    
    // If the page table is not present, create it
    if(!pdir[virt >> 22]) {
        if(!vmm_create_page_table(pdir, virt, flags)) {
            return NULL;
        }
    }
    // Map the address to the page table
    // Use the virtual address to get the index in the page directory and keep only the first 12 bits
    // which is the page table and use the virtual address to find the index in the page table
    ((uint32_t *) (pdir[virt >> 22] & ~0xFFF))[virt << 10 >> 10 >> 12] = phys | flags;
    return 1;
}

/**
 * Maps the physical address to the virtual one
 */
int vmm_map_phys(page_dir_t *pdir, vmm_addr_t virt, mm_addr_t phys, uint32_t flags) {
    // If the page table is not present, create it
    if(pdir[virt >> 22] == 0) {
        if(!vmm_create_page_table(pdir, virt, flags)) {
            return NULL;
        }
    }
    // Map the address to the page table
    // Use the virtual address to get the index in the page directory and keep only the first 12 bits
    // which is the page table and use the virtual address to find the index in the page table
    ((uint32_t *) (pdir[virt >> 22] & ~0xFFF))[virt << 10 >> 10 >> 12] = phys | flags;
    return 1;
}

/**
 * Gets the physical address from the given virtual address
 */
void *get_phys_addr(page_dir_t *pdir, vmm_addr_t virt) {
    if(pdir[virt >> 22] == NULL)
        return NULL;
    return (void *) (((uint32_t *) (pdir[virt >> 22] & ~0xFFF))[virt << 10 >> 10 >> 12] >> 12 << 12);
}

/**
 * Creates a page directory to be used with a process
 */
page_dir_t *create_address_space() {
    // Allocate space for a page directory
    page_dir_t *pdir = (page_dir_t *) page_table_malloc();
    if(!pdir)
        return NULL;
    // Clone page directory
    int i;
    vmm_addr_t addr = 0;
    for(i = 0; i < PAGEDIR_SIZE; i++, addr += KERNEL_SPACE_END) {
        if(kern_dir[i] & PAGE_PRESENT) {
            if(!vmm_create_page_table(pdir, addr, kern_dir[i] << 20 >> 20)) {
                return NULL;
            }
            memcpy((void *) (pdir[i] >> 12 << 12), (void *) (kern_dir[i] >> 12 << 12), PAGE_SIZE);
        }
    }
    return pdir;
}

/**
 * Deletes a page directory
 */
void delete_address_space(page_dir_t *pdir) {
    for(int i = 0; i < PAGEDIR_SIZE; i++) {
        if(pdir[i * PAGE_SIZE >> 22]) {
            vmm_unmap_page_table(pdir, i * PAGE_SIZE);
        }
    }
}

/**
 * Unmaps the page table and frees the memory block
 */
void vmm_unmap_page_table(page_dir_t *pdir, vmm_addr_t virt) {
    void *frame = (void *) (pdir[virt >> 22] & PAGE_FRAME_MASK);
    page_table_free(frame);
    pdir[virt >> 22] = NULL;
    flush_tlb(virt);
}

/**
 * Unmaps the physical address from the virtual and deallocates memory
 */
void vmm_unmap(page_dir_t *pdir, vmm_addr_t virt) {
    if(pdir[virt >> 22] != NULL) {
        void *addr = get_phys_addr(pdir, virt);
        if(addr) {
            pmm_free(addr);
            ((uint32_t *) (pdir[virt >> 22] & ~0xFFF))[virt << 10 >> 10 >> 12] = 0;
        } else {
            __printk("Error unmapping memory\n");
        }
    }
}

/**
 * Unmaps a physical address from the virtual
 */
void vmm_unmap_phys(page_dir_t *pdir, vmm_addr_t virt) {
    if(pdir[virt >> 22] != NULL) {
        ((uint32_t *) (pdir[virt >> 22] & ~0xFFF))[virt << 10 >> 10 >> 12] = 0;
    }
}

#define MAX_BLOCKS 512
#define PAGE_START 0x200000

// 16B to hold up 2 MB of paging structures
static uint32_t bitmap[0x10];
static int used_blocks = 0;

/**
 * Allocates space for a page table
 */
void *page_table_malloc() {
    int p = paging_first_free();
    if(p == -1)
        return NULL;
    paging_set_bit(p);
    used_blocks++;
    void *addr = (void *) ((BLOCKS_LEN * p) + PAGE_START);
    memset(addr, 0, PAGE_SIZE);
    return addr;
}

/**
 * Sets the block as used
 */
void paging_set_bit(int bit) {
    bitmap[bit / 32] |= (1 << (bit % 32));
}

/**
 * Sets the block as free
 */
void paging_unset_bit(int bit) {
    bitmap[bit / 32] &= ~(1 << (bit % 32));
}

/**
 * Gets the first free block
 */
int paging_first_free() {
    uint32_t i;
    int j;
    
    for(i = 0; i < MAX_BLOCKS / 32; i++) {
        if(bitmap[i] != BYTE_SET) {
            for(j = 0; j < 32; j++) {
                if(!(bitmap[i] & (1 << j))) {
                    return (i * 32) + j;
                }
            }
        }
    }
    return -1;
}

/**
 * Frees a block
 */
void page_table_free(void *addr) {
    paging_unset_bit(((uint32_t) addr / BLOCKS_LEN) - PAGE_START);
    used_blocks--;
}

/**
 * Returns the bitmap representing the page table.
 *
 * @return A pointer to the bitmap representing the page table.
 *
 * @throws None
 */


uint32_t *get_page_table_bitmap() {
    return bitmap;
}