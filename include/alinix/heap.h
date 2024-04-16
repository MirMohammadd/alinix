#ifndef _ALINIX_KERNEL_HEAP_H
#define _ALINIX_KERNEL_HEAP_H


#include <alinix/types.h>
#ifndef align_up
#define align_up(num, align) \
    (((num) + ((align) - 1)) & ~((align) - 1))
#endif

uint32_t pageRoundUp(uint32_t address);
uint32_t pageRoundDown(uint32_t address);

#define HEAP_INCREASE_SIZE 10_MB

struct MemoryHeader
{
    struct MemoryHeader* next;
    struct MemoryHeader* prev;
    bool allocated;
    uint32_t size;
} __attribute__((packed));
bool CheckForErrors();

#endif /*_ALINIX_KERNEL_HEAP_H*/