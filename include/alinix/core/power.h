#ifndef __ALINIX_KERNEL_CORE_POWER_H
#define __ALINIX_KERNEL_CORE_POWER_H

#include <alinix/types.h>

struct RSDPtr
{
    uint8_t Signature[8];
    uint8_t CheckSum;
    uint8_t OemID[6];
    uint8_t Revision;
    uint32_t* RsdtAddress;
};

struct FACP
{
    uint8_t Signature[4];
    uint32_t Length;
    uint8_t unneded1[40 - 8];
    uint32_t* DSDT;
    uint8_t unneded2[48 - 44];
    uint32_t* SMI_CMD;
    uint8_t ACPI_ENABLE;
    uint8_t ACPI_DISABLE;
    uint8_t unneded3[64 - 54];
    uint32_t* PM1a_CNT_BLK;
    uint32_t* PM1b_CNT_BLK;
    uint8_t unneded4[89 - 72];
    uint8_t PM1_CNT_LEN;
}; 


unsigned int* acpiCheckRSDPtr(unsigned int* ptr);
unsigned int* acpiGetRSDPtr(void);
int acpiCheckHeader(unsigned int* ptr, char* sig);
int acpiEnable(void);
int initAcpi(void);

#endif /*__ALINIX_KERNEL_CORE_POWER_H*/