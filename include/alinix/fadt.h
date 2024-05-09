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


struct RSDT {
  struct ACPISDTHeader h;
  uint32_t PointerToOtherSDT[];  // Flexible array member
};

struct XSDT {
  struct ACPISDTHeader h;
  uint64_t PointerToOtherSDT[];  // Flexible array member
};

bool fadtChecksum(struct ACPISDTHeader *tableHeader);
void *findFACP(void *RootSDT);
#endif
