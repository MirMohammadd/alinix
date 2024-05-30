/**
 * @author Ali Mirmohammad
 * @file fat.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Fat file system driver.
*/

#include <alinix/fs/fat.h>
#include <alinix/memory.h>
#include <alinix/types.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Fat file system driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


Disk* Disk_create(uint32_t controllerIndex, void* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize){
    /**
     * @brief Creates a disk for the file system FAT
    */
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