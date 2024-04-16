#include <alinix/virtualmemory.h>


mapVirtualToPhysical(void* physAddress, void* virtAddress, bool kernel, bool writeable)
{
    struct PageTableEntry* page = GetPageForAddress((uint32_t)virtAddress, true, writeable, !kernel);

    page->frame = (uint32_t)physAddress / PAGE_SIZE;
    page->isUser = kernel ? 0 : 1;
    page->readWrite = writeable ? 1 : 0;
    page->present = 1;

    invlpg(virtAddress);
}