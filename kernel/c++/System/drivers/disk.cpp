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
// #include <alinix/disk.hpp>

// DiskUtil::DiskUtil(uint32_t controllerIndex, DiskController* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize)
// {
//     this->controllerIndex = controllerIndex;
//     this->controller = controller;
//     this->type = type;
//     this->size = size;
//     this->blockSize = blocksize;
//     this->numBlocks = blocks;
// }

// char DiskUtil::ReadSector(uint32_t lba, uint8_t* buf)
// {
//     #if ENABLE_ADV_DEBUG
//     System::statistics.diskReadOp += 1;
//     #endif

//     if(this->controller != 0)
//         return this->controller->ReadSector(this->controllerIndex, lba, buf);
//     return 1;
// }
// char DiskUtil::WriteSector(uint32_t lba, uint8_t* buf)
// {
//     #if ENABLE_ADV_DEBUG
//     System::statistics.diskWriteOp += 1;
//     #endif

//     if(this->controller != 0)
//         return this->controller->WriteSector(this->controllerIndex, lba, buf);
//     return 1;
// }