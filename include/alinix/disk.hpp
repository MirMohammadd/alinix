#ifndef __ALINIX_KERNEL_DISK_HPP
#define __ALINIX_KERNEL_DISK_HPP


#include <alinix/types.h>

class DiskController;

enum DiskType
{
    HardDisk,
    USBDisk,
    Floppy,
    CDROM
};

class Disk
{
public:
    DiskController* controller;         // Which controller is controling this disk device
    uint32_t controllerIndex;   // The real number for the disk on the controller
    char* identifier = 0;               // Disk Identifier
    DiskType type;              // Type of disk
    uint64_t size;      // Size of disk in bytes
    uint32_t numBlocks; // Number of data blocks
    uint32_t blockSize; // Size of one block of data

    Disk(uint32_t controllerIndex, DiskController* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize);
    
    virtual char ReadSector(uint32_t lba, uint8_t* buf);          
    virtual char WriteSector(uint32_t lba, uint8_t* buf);
};

#endif