/**
 * @author Ali Mirmohammad
 * @file vfs.c
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
 *  - Virtual file system .
*/


#include <alinix/vfs/virtualfilesystem.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Virtual File System")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

/**
 * @brief Creates a new VirtualFileSystem object.
 *
 * This function creates a new VirtualFileSystem object by performing the following steps:
 * 1. Allocates memory for the VirtualFileSystem structure using `malloc`.
 * 2. Initializes the `disk` member of the VirtualFileSystem structure with the provided `disk` parameter.
 * 3. Initializes the `StartLBA` member of the VirtualFileSystem structure with the provided `start` parameter.
 * 4. Initializes the `SizeInSectors` member of the VirtualFileSystem structure with the provided `size` parameter.
 * 5. If the `name` parameter is not `NULL`, initializes the `Name` member of the VirtualFileSystem structure with the provided `name` parameter. Otherwise, initializes it with the string "Unkown".
 * 6. Returns a pointer to the newly created VirtualFileSystem object.
 *
 * @param disk A pointer to the Disk object representing the disk on which the VirtualFileSystem is located.
 * @param start The starting LBA (Logical Block Address) of the VirtualFileSystem.
 * @param size The size of the VirtualFileSystem in sectors.
 * @param name A pointer to a character array representing the name of the VirtualFileSystem. If `NULL`, the name is set to "Unkown".
 *
 * @return A pointer to the newly created VirtualFileSystem object.
 *
 * @note The function assumes that the `malloc` function is available for allocating memory.
 *
 * @example
 * Disk* disk = Disk_create("MyDisk", 1024);
 * VirtualFileSystem* vfs = VirtualFileSystem_create(disk, 0, 100, "MyVFS");
 */
VirtualFileSystem* VirtualFileSystem_create(Disk* disk, uint32_t start, uint32_t size, char* name) {
    VirtualFileSystem* vfs = (VirtualFileSystem*)malloc(sizeof(VirtualFileSystem));
    vfs->disk = disk;
    vfs->StartLBA = start;
    vfs->SizeInSectors = size;
    if (name != NULL) {
        vfs->Name = name;
    } else {
        vfs->Name = "Unkown";
    }
    return vfs;
}