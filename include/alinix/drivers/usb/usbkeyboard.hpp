#ifndef __ALINIX_KERNEL_INCLUDED_DRIVERS_USB_USB_KEYBOARD_H
#define __ALINIX_KERNEL_INCLUDED_DRIVERS_USB_USB_KEYBOARD_H

#include <alinix/types.h>
#include "usbdevice.hpp"
#include "usbdriver.hpp"
#include "keyboard.hpp"


namespace alinix{
    namespace drivers{
        namespace usb{
        class USBKeyboard : public USBDriver, public Keyboard
            {
            private:
                int InInterruptEndpoint = -1;

                uint8_t prevPacket[8];
            public:
                // Instance initializer
                USBKeyboard(USBDevice* dev);
                
                // Called when mass storage device is plugged into system
                bool Initialize() override;

                // Called when mass storage device is unplugged from system
                void DeInitialize() override;

                // Called by USB driver when we receive a interrupt packet
                bool HandleInterruptPacket(InterruptTransfer_t* transfer) override;

                // Update LED's on a keyboard device
                void UpdateLEDS() override;
            };
        }
    }
}

#endif /*__ALINIX_KERNEL_INCLUDED_DRIVERS_USB_USB_KEYBOARD_H*/