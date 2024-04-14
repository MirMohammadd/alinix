#include <lib/string.h>
#include <mm/memory.h>

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

uint32_t *get_page_table_bitmap() {
    return bitmap;
}