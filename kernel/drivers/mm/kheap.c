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

/**
 * @abstraction:
 *  - Kernel heap memory stuff header operations.
*/
#include <alinix/kernel.h>
#include <alinix/mm.h>
#include <alinix/xheap.h>

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

int get_heap_size() {
    return heap_info.size;
}

int get_used_heap() {
    return heap_info.used;
}

void print_header(heap_header_t *head) {
    printk("Size: %d Is free: %d Next: %x\n", head->size, head->is_free, head->next);
}