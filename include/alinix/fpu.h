#ifndef __ALINIX_KERNEL_FPU_H
#define __ALINIX_KERNEL_FPU_H

#include <alinix/types.h>

struct FPUControlWord
{
    uint8_t InvalidOperand : 1;
    uint8_t DenormalOperand : 1;
    uint8_t ZeroDevide : 1;
    uint8_t Overflow : 1;
    uint8_t Underflow : 1;
    uint8_t Precision : 1;
    uint8_t reserved1 : 1;
    uint8_t reserved2 : 1;
    uint8_t PrecisionControl : 2;
    uint8_t RoundingControl : 2;
    uint8_t InfinityControl : 1;
    uint8_t reserved3 : 3;
} __attribute__((packed));

static void Enable();

#endif /*__ALINIX_KERNEL_FPU_H*/