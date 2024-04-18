#include <alinix/heap.h>
#include <alinix/memory.h>
//? Use Malloc in heap.h or  memory.h ???

bool CheckForErrors()
{
    /*Keep here empty*/
}

uint32_t pageRoundUp(uint32_t address)
{
    if((address & 0xFFFFF000) != address)
    {
        address &= 0xFFFFF000;
        address += 0x1000;
    }
    return address;
}

uint32_t pageRoundDown(uint32_t address)
{
    return address & 0xFFFFF000;
}

void allignedFree(void* ptr)
{
    if(ptr == 0)
        return;

    uint16_t offset = *((uint16_t*)ptr - 1);

    void* p = (void*)((uint8_t*)ptr - offset);
    // TODO : Implement freeing of memory pages
    Free(p);
}

void* alignedMalloc(uint32_t size, uint32_t align)
{
    void* ptr = 0;

    if(!(align & (align - 1)) == 0)
        return 0;

    if(align && size)
    {
        uint32_t hdr_size = sizeof(uint16_t) + (align - 1);

        void* p = malloc(size + hdr_size);

        if(p)
        {
            ptr = (void *) align_up(((uintptr_t)p + sizeof(uint16_t)), align);

            *((uint16_t*)ptr - 1) = (uint16_t)((uintptr_t)ptr - (uintptr_t)p);
        }
    }
    return ptr;
}

void Free(void* ptr)
{
    struct MemoryHeader* chunk = (struct MemoryHeader*)((uint32_t)ptr - sizeof(struct MemoryHeader));
    
    chunk -> allocated = false;
    
    if(chunk->prev != 0 && !chunk->prev->allocated)
    {
        chunk->prev->next = chunk->next;
        chunk->prev->size += chunk->size + sizeof(struct MemoryHeader);
        if(chunk->next != 0)
            chunk->next->prev = chunk->prev;
        
        chunk = chunk->prev;
    }
    
    if(chunk->next != 0 && !chunk->next->allocated)
    {
        chunk->size += chunk->next->size + sizeof(struct MemoryHeader);
        chunk->next = chunk->next->next;
        if(chunk->next != 0)
            chunk->next->prev = chunk;
    }
}