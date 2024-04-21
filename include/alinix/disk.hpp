/**
 * @author Ali Mirmohammad
 * @file disk.hpp
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
 * Abstraction:
 *   - Provide interfaces and utilities for the disk controller
*/


#ifndef __ALINIX_KERNEL_DISK_HPP
#define __ALINIX_KERNEL_DISK_HPP


#include <alinix/types.h>

class DiskController;

#include <alinix/enums.h>

class DiskUtil
{
public:
    DiskController* controller;         // Which controller is controlling this DiskUtil device
    uint32_t controllerIndex;           // The real number for the DiskUtil on the controller
    char* identifier = nullptr;         // DiskUtil Identifier
    DiskType type;                      // Type of diskUtil
    uint64_t size;                      // Size of DiskUtil in bytes
    uint32_t numBlocks;                 // Number of data blocks
    uint32_t blockSize;                 // Size of one block of data
    USBDriver* handler;                 // Pointer to the USB driver

    DiskUtil(uint32_t controllerIndex, DiskController* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize, USBDriver* usbDriver)
        : controller(controller), controllerIndex(controllerIndex), type(type), size(size), numBlocks(blocks), blockSize(blocksize), handler(usbDriver)
    {
        // Initialize other members if needed
    }

    virtual char ReadSector(uint32_t lba, uint8_t* buf);

    virtual char WriteSector(uint32_t lba, uint8_t* buf);
};

#endif