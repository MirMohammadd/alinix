#ifndef __ALINIX_KERNEL_RSPD_ACPI_H
#define __ALINIX_KERNEL_RSPD_ACPI_H


/**
 * @ref https://wiki.osdev.org/RSDP
*/


#define ACPI_VERSION "1.0"

#include <alinix/compiler.h>
#include <alinix/types.h>

struct RSDP_t{
    char Sign[8];
    u8 check_sum;
    char QEMID[6];
    u8 revision;
    u32 RsdtAddress;
}__attribute__ ((packed));

struct XSDP_t {
 char Signature[8];
 uint8_t Checksum;
 char OEMID[6];
 uint8_t Revision;
 uint32_t RsdtAddress;      // deprecated since version 2.0
 
 uint32_t Length;
 uint64_t XsdtAddress;
 uint8_t ExtendedChecksum;
 uint8_t reserved[3];
} __attribute__ ((packed));


#endif