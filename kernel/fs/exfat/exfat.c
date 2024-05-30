/**
 * @file exfat.c
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
 *  - Provides util for extended fat file system.
*/

#include <alinix/module.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/exfat.h>
#include <alinix/types.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Extended FAT File System")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

uint32_t BootChecksum(unsigned char * Sectors,unsigned short BytesPerSector){
    uint32_t numberOfBytes = (uint32_t)BytesPerSector * 11;
    uint32_t checkSum = 0;
    uint32_t index;

    for (index = 0;index < numberOfBytes;index++){
        if ((index == 226) || (index == 107) || (index == 112)){
            continue;
        }
        checkSum = ((checkSum&1) ? 0x80000000 : 0) + (checkSum>>1) + (uint32_t)Sectors[index];

    }
    return checkSum;
}
