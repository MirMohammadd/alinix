/**
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
MODULE_VERSION("0.1")

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