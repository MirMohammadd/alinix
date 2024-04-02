#include <system/memory/deviceheap.h>
#include <system/memory/heap.h>
#include <system/log.h>

using namespace HeisenOs;
using namespace HeisenOs::common;
using namespace HeisenOs::core;
using namespace HeisenOs::system;

uint32_t DeviceHeap::currentAddress = DEVICE_HEAP_START;

uint32_t DeviceHeap::AllocateChunk(uint32_t size)
{
    uint32_t ret = DeviceHeap::currentAddress;
    DeviceHeap::currentAddress += pageRoundUp(size);

    // Will propably never happen
    if(DeviceHeap::currentAddress >= DEVICE_HEAP_END)
        Log(Error, "Device heap is getting to big!");
    
    return ret;
}