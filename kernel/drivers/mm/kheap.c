/**
 * @author Ali Mirmohammad
 * @file kheap.c
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
 *  - Kernel heap memory stuff header operations.
*/
#include <alinix/kernel.h>
#include <alinix/mm.h>
#include <alinix/xheap.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel heap memory stuff header operations.")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")

#define HEAP_END 0x200000

heap_info_t heap_info;
uint32_t kernel_start;
uint32_t kernel_end;
/**
 * Init the kernel heap memory
 */
void kheap_init() {
    heap_info.start = (vmm_addr_t *) &kernel_end;
    heap_info.size = HEAP_END - (int) &kernel_end;
    heap_info.used = sizeof(heap_header_t);
    heap_info.first_header = (heap_header_t *) heap_info.start;
    heap_info.first_header->magic = HEAP_MAGIC;
    heap_info.first_header->size = heap_info.size - heap_info.used;
    heap_info.first_header->is_free = 1;
    heap_info.first_header->next = NULL;
}

/**
 * Allocates a block of memory of the specified length.
 *
 * This function allocates a block of memory of the specified length by calling the `first_free`
 * function. The `first_free` function searches for the first block of free memory that is large
 * enough to hold the requested length, and returns a pointer to that block. The `kmalloc` function
 * simply calls `first_free` and returns the resulting pointer.
 *
 * @param len The length of the memory block to allocate.
 *
 * @return A pointer to the allocated memory block, or NULL if there is not enough free memory
 *         to satisfy the request.
 *
 * @throws None
 */
void *kmalloc(size_t len) {
    return first_free(len);
}

void kfree(void *ptr) {
    heap_header_t *head = ptr - sizeof(heap_header_t);
    if((head->is_free == 0) && (head->magic == HEAP_MAGIC)) {
        head->is_free = 1;
        heap_info.used -= head->size;
        
        // Merge contiguous free sections
        heap_header_t *app = head->next;
        while((app != NULL) && (app->is_free == 1)) {
            head->size += app->size + sizeof(heap_header_t);
            head->next = app->next;
            
            app = app->next;
        }
    }
}

/**
 * Frees a block of memory previously allocated by `kmalloc`.
 *
 * This function frees a block of memory that was previously allocated by `kmalloc`. It takes a
 * pointer to the memory block to free, and searches for the corresponding heap header that was
 * placed before the block. If the header is valid and the block is not already free, the function
 * marks the block as free in the heap header, updates the heap information, and merges any
 * contiguous free sections with the freed block.
 *
 * @param ptr A pointer to the memory block to free.
 *
 * @throws None
 */
void *first_free(size_t len) {
    heap_header_t *head = (heap_header_t *) heap_info.first_header;
    
    if(heap_info.used >= heap_info.size)
        return NULL;
    
    while(head != NULL) {
        if((head->size >= len) && (head->is_free == 1) && (head->magic == HEAP_MAGIC)) {
            head->is_free = 0;
            heap_header_t *head2 = (heap_header_t *) head + len + sizeof(heap_header_t);
            head2->size = head->size - len - sizeof(heap_header_t);
            head2->magic = HEAP_MAGIC;
            head2->is_free = 1;
            head2->next = NULL;
            head->next = head2;
            head->size = len;
            heap_info.used += len + sizeof(heap_header_t);
            return (void *) head + sizeof(heap_header_t);
        }
        head = head->next;
    }
    return NULL;
}

/**
 * Returns the size of the heap.
 *
 * This function returns the size of the heap, which is the total amount of memory that is
 * available for allocation by the `kmalloc` function. The size is stored in the `heap_info`
 * structure, and is accessed by this function.
 *
 * @return The size of the heap, in bytes.
 *
 * @throws None
 */
int get_heap_size() {
    return heap_info.size;
}

/**
 * Returns the amount of memory currently in use by the heap.
 *
 * This function returns the amount of memory that is currently in use by the heap, which is the
 * total amount of memory that has been allocated by the `kmalloc` function and has not been freed
 * by the `kfree` function. The amount of used heap memory is stored in the `heap_info` structure,
 * and is accessed by this function.
 *
 * @return The amount of memory currently in use by the heap, in bytes.
 *
 * @throws None
 */
int get_used_heap() {
    return heap_info.used;
}

/**
 * Prints the information stored in a heap header.
 *
 * This function prints the information stored in a heap header, which includes the size of the
 * block, whether the block is free or not, and the address of the next block in the heap. The
 * information is printed using the `printk` function, which is a simple printf-like function for
 * printing to the console.
 *
 * @param head A pointer to the heap header to print.
 *
 * @throws None
 */
void print_header(heap_header_t *head) {
    printk("Size: %d Is free: %d Next: %x\n", head->size, head->is_free, head->next);
}