#include <alinix/disk.hpp>

DiskUtil::DiskUtil(uint32_t controllerIndex, DiskController* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize)
{
    this->controllerIndex = controllerIndex;
    this->controller = controller;
    this->type = type;
    this->size = size;
    this->blockSize = blocksize;
    this->numBlocks = blocks;
}