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
 *  - Provides util for extended fat file system in header file.
*/

#include <alinix/types.h>

struct bootsector {
	char jump[3];
	char fsid[8];
	char pad[53];
	uint64_t unk; // sectors before first cluster too?
	uint64_t fsSizeInSectors;
        uint32_t sectorsToStartOfFat;
        uint32_t sectorsUsedForFat;
        uint32_t sectorStartOfFirstCluster;
        uint32_t clusterCountInFs;
        uint32_t clusterForRootDirectory;
        uint32_t unk[2];
        uint8_t logBytesPerSector, logSectorsPerCluster, fatCount, driveId; // 2-log for both. bytesPerCluster = 1 << (logBytesPerSector + logSectorsPerCluster).
        uint8_t percentInUse; // for display ala windows computer explorer
        uint8_t unk[7];
        char bootcode[390];
        char bootsign[2];
};

uint32_t BootChecksum(unsigned char * Sectors,unsigned short BytesPerSector);