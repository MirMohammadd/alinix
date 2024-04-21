#ifndef __ALINIX_KERNEL_DISKUtil_HPP
#define __ALINIX_KERNEL_DISKUtil_HPP


#include <alinix/types.h>

class DiskUtilController;

enum DiskUtilType
{
    HardDiskUtil,
    USBDiskUtil,
    Floppy,
    CDROM
};

class DiskUtil
{
public:
    DiskUtilController* controller;         // Which controller is controling this diskUtil device
    uint32_t controllerIndex;   // The real number for the diskUtil on the controller
    char* identifier = 0;               // DiskUtil Identifier
    DiskUtilType type;              // Type of diskUtil
    uint64_t size;      // Size of diskUtil in bytes
    uint32_t numBlocks; // Number of data blocks
    uint32_t blockSize; // Size of one block of data

    DiskUtil(uint32_t controllerIndex, DiskUtilController* controller, DiskUtilType type, uint64_t size, uint32_t blocks, uint32_t blocksize);
    
    virtual char ReadSector(uint32_t lba, uint8_t* buf);          
    virtual char WriteSector(uint32_t lba, uint8_t* buf);
};

#endif