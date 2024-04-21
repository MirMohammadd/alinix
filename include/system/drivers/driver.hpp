#ifndef __ALINIX_KERNEL_SYSTEM_DRIVERS_HPP
#define __ALINIX_KERNEL_SYSTEM_DRIVERS_HPP

#ifndef __cplusplus
# error "This file must be compiled with C++"

#endif


#include <system/drivers/usb/usbdevice.h>
#include <system/drivers/usb/usbdevice.hpp>

// typedef USBDevice USBDevice;



static char* GetDriverName();
static char* GetDriverDescription();

static bool Initialize();


#endif //__ALINIX_KERNEL_SYSTEM_DRIVERS_HPP