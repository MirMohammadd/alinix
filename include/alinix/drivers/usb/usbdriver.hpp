#ifndef __ALINIX_KERNEL_DRIVER_INCLUDED_USB_DRIVER_HPP
#define __ALINIX_KERNEL_DRIVER_INCLUDED_USB_DRIVER_HPP

#include "driver.hpp"

using namespace alinix;

namespace alinix{
    namespace drivers{
        namespace usb{
        typedef struct InterruptTransfer InterruptTransfer_t;

        class USBDriver : public drivers::usb::Driver
        {
        public:
            // Which device is this driver for
            USBDevice* device;
        public:
            USBDriver(USBDevice* dev, char* driverName);
            virtual ~USBDriver();

            // De-Active this driver from the system
            // Called when device is unplugged
            virtual void DeInitialize();

            // Called from USB Controller when a interrupt packet is received
            virtual bool HandleInterruptPacket(InterruptTransfer_t* transfer);
        };
        }
    }
}

#endif /*__ALINIX_KERNEL_DRIVER_INCLUDED_USB_DRIVER_HPP*/