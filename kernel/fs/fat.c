#include <alinix/fs/fat.h>
#include <alinix/memory.h>
#include <alinix/types.h>

Disk* Disk_create(uint32_t controllerIndex, void* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize){
    Disk* disk = (Disk*)malloc(sizeof(Disk));
    disk->controllerIndex = controllerIndex;
    disk->controller = controller;
    disk->type = type;
    disk->size = size;
    disk->numBlocks = blocks;
    disk->blockSize = blocksize;
    disk->identifier = NULL; // Allocate and set identifier if needed
    return disk;
}