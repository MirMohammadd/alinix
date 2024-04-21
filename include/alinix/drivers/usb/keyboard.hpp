#ifndef __ALINIX_KERNEL_KEYBOARD_DRIVERS_HPP
#define __ALINIX_KERNEL_KEYBOARD_DRIVERS_HPP

#include <alinix/types.h>

namespace alinix{
    namespace drivers{
        namespace usb{
                    struct InternalKeyboardStatus
        {
            bool LeftShift;
            bool RightShift;

            bool Alt;
            bool AltGr;
            
            bool LeftControl;
            bool RightControl;
        };

        // Structure for shared modifier keys between keyboards
        struct KeyboardStatus
        {
            bool CapsLock;
            bool NumLock;
        };
        
        // Types of keyboards currently supported
        enum KeyboardType
        {
            PS2,
            USB
        };

        // Interface for providing a common access for all keyboard devices
        class Keyboard
        {
        public:
            KeyboardType type;
            InternalKeyboardStatus status;
        public:
            Keyboard(KeyboardType type);

            // Update LED's on a keyboard device
            virtual void UpdateLEDS();
            
            // Checks if the buffer contains the given key, also returns position of key
            bool ContainsKey(uint8_t key, uint8_t* packet, int* pos);
        };
        }
    }
}

#endif /*__ALINIX_KERNEL_KEYBOARD_DRIVERS_HPP*/