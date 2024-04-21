#ifndef __ALINIX_KERNEL_USB_CONTROLLER_SYSTEM_HPP
#define __ALINIX_KERNEL_USB_CONTROLLER_SYSTEM_HPP


#include <alinix/types.h>
#include <system/drivers/usb/usbdriver.hpp>
#include <system/drivers/usb/usbdevice.hpp>
#include <alinix/list.hpp>

// typedef struct InterruptTransfer
// {
//     uint8_t* bufferPointer;
//     uint32_t bufferPhys;
//     int bufferLen;

//     USBDriver* handler;
//     int queueIndex;

//     uint32_t tdPhys;
//     void* td;
//     int numTd;

//     void* qh;
//     int endpoint;
// } InterruptTransfer_t;

enum USBControllerType
{
    UHCI,
    OHCI,
    EHCI,
    xHCI
};

// typedef struct InterruptTransfer
// {
//     uint8_t* bufferPointer;
//     uint32_t bufferPhys;
//     int bufferLen;

//     USBDriver* handler;
//     int queueIndex;

//     uint32_t tdPhys;
//     void* td;
//     int numTd;

//     void* qh;
//     int endpoint;
// } InterruptTransfer_t;


#endif /*__ALINIX_KERNEL_USB_CONTROLLER_SYSTEM_HPP*/