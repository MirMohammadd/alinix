#ifndef __ALINIX_KERNEL_CTRL_H
#define __ALINIX_KERNEL_CTRL_H



#include <alinix/types.h>

typedef void USBDriver;

typedef struct InterruptTransfer
{
    uint8_t* bufferPointer;
    uint32_t bufferPhys;
    int bufferLen;

    USBDriver* handler;
    int queueIndex;

    uint32_t tdPhys;
    void* td;
    int numTd;

    void* qh;
    int endpoint;
} InterruptTransfer_t;

#endif