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


#ifndef __ALINIX_KERNEL_DISKUtil_HPP
#define __ALINIX_KERNEL_DISKUtil_HPP


#include <alinix/types.h>

class DiskUtilController;

#include <alinix/enums.h>

class DiskUtil
{
public:
    DiskUtilController* controller;         // Which controller is controling this diskUtil device
    uint32_t controllerIndex;   // The real number for the diskUtil on the controller
    char* identifier = 0;               // DiskUtil Identifier
    DiskType type;              // Type of diskUtil
    uint64_t size;      // Size of diskUtil in bytes
    uint32_t numBlocks; // Number of data blocks
    uint32_t blockSize; // Size of one block of data

    DiskUtil(uint32_t controllerIndex, DiskUtilController* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize);
    
    virtual char ReadSector(uint32_t lba, uint8_t* buf);          
    virtual char WriteSector(uint32_t lba, uint8_t* buf);
};

#endif