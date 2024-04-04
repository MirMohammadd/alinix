#ifndef _HEISEN_KERNEL_OS_ATA_H
#define _HEISEN_KERNEL_OS_ATA_H

#define ATA_DATA_PORT 0x1F0
#define ATA_FEATURES_PORT 0x1F1
#define ATA_SECTOR_COUNT_PORT 0x1F2
#define ATA_LBA_LOW_PORT 0x1F3
#define ATA_LBA_MID_PORT 0x1F4
#define ATA_LBA_HIGH_PORT 0x1F5
#define ATA_DRIVE_SELECT_PORT 0x1F6
#define ATA_COMMAND_PORT 0x1F7
#define ATA_STATUS_PORT 0x1F7

#define ATA_IDENTIFY_COMMAND 0xEC

#include <types.h>
uint64_t ata_identify_drive(uint8_t drive);

double getDriveSize(uint8_t driveInBytes);


#endif 