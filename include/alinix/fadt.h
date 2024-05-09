#ifndef __ALINIX_KERNEL_FADT_H
#define __ALINIX_KERNEL_FADT_H


/**
 * @ref https://wiki.osdev.org/RSDT
*/

#include <alinix/types.h>


struct ACPISDTHeader {
  char Signature[4];
  uint32_t Length;
  uint8_t Revision;
  uint8_t Checksum;
  char OEMID[6];
  char OEMTableID[8];
  uint32_t OEMRevision;
  uint32_t CreatorID;
  uint32_t CreatorRevision;
};


bool fadtChecksum(struct ACPISDTHeader *tableHeader);

#endif
