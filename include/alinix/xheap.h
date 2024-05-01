#ifndef __ALINIX_KERNEL_X_HEAP_H
#define __ALINIX_KERNEL_X_HEAP_H

#include <alinix/types.h>
#include <alinix/mm.h>

#define HEAP_MAGIC      0xA0B0C0


typedef struct heap_header {
    int magic; // sanity check: 0xA0B0C0
    size_t size;
    int is_free;
    struct heap_header *next;
} heap_header_t;

typedef struct {
    size_t size;
    vmm_addr_t *start;
    size_t used;
    heap_header_t *first_header;
} heap_info_t;

void heap_init(vmm_addr_t *addr);
void *umalloc(size_t len, vmm_addr_t *heap);
void ufree(void *ptr, vmm_addr_t *heap);
void *umalloc_sys(size_t len);
void ufree_sys(void *ptr);

#endif