#ifndef __ALINIX_KERNEL_POWER_OFF_H
#define __ALINIX_KERNEL_POWER_OFF_H

#include <alinix/types.h>

struct powerOff{
    u16 *SMI_CMD;
    byte ACPI_ENABLE;
    byte ACPI_DISABLE;
    u16 *PM1a_CNT;
    u16 *PM1b_CNT;
    char SLP_TYPa;
    char SLP_TYPb;
    char SLP_EN;
    char SCI_EN;
    byte PM1_CNT_LEN;
};

#endif