#include <alinix/heap.h>

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