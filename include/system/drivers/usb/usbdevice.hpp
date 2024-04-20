#ifndef __ALINIX_KERNEL_USB_DEVICE_SYSTEM_HPP
#define __ALINIX_KERNEL_USB_DEVICE_SYSTEM_HPP

#ifndef __cplusplus
# error "This file must be compiled with C++"

#endif




#include <alinix/types.h>
#include <system/drivers/usb/usbdriver.hpp>

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

#endif /*__ALINIX_KERNEL_USB_CONTROLLER_SYSTEM_HPP*/
