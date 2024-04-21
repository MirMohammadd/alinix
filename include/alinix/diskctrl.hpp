#ifndef __ALINIX_KERNEL_DISK_CTRL_HPP
#define __ALINIX_KERNEL_DISK_CTRL_HPP

#include <alinix/types.h>

class DiskController
{       
public:
    DiskController();

    virtual char ReadSector(uint16_t drive, uint32_t lba, uint8_t* buf);
    virtual char WriteSector(uint16_t drive, uint32_t lba, uint8_t* buf);   
    virtual bool EjectDrive(uint8_t drive);         
};

#endif 