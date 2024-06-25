/**
 * @author Ali Mirmohammad
 * @file vtoc.c
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
 *  Implemented VTOC for the file system kernel.
*/
#include <alinix/VTOC.h>
#include <alinix/memory.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("VTOC for the file system kernel")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")

/**
 * @brief Get the CHR (Cylinder-Head-Record) information from the VTOC (Volume Table of Contents).
 *
 * This function extracts the cylinder, head, and record information from the VTOC buffer.
 * The VTOC buffer is expected to contain the necessary data at specific offsets.
 *
 * @param buffer Pointer to the VTOC buffer.
 *
 * @return void
 *
 * @throws None
 */
void GetCHRFromVTOC(void *buffer){
    uint16_t cyl,head;
    uint8_t rec;
    memcpy(& cyl,buffer + 15,2);
    memcpy(&head,buffer + 17,2);
    memcpy(&rec,buffer + 19,1);
    RET;
}

