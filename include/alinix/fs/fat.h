#include <alinix/types.h>
#include <alinix/enums.h>

Disk* Disk_create(uint32_t controllerIndex, void* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize);


char Disk_ReadSector(Disk* disk, uint32_t lba, uint8_t* buf);
char Disk_WriteSector(Disk* disk, uint32_t lba, uint8_t* buf);
