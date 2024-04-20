#ifndef __ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP
#define __ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP


#include <system/drivers/driver.h>
#include <system/drivers/driver.hpp>


        typedef struct InterruptTransfer InterruptTransfer_t;

        class USBDriver : public Driver
        {
        public:
            // Which device is this driver for
            class USBDevice* device;
        public:
            USBDriver(class USBDevice* dev, char* driverName);
            virtual ~USBDriver();

            // De-Active this driver from the system
            // Called when device is unplugged
            virtual void DeInitialize();

            // Called from USB Controller when a interrupt packet is received
            virtual bool HandleInterruptPacket(InterruptTransfer_t* transfer);
        };


#endif /*__ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP*/