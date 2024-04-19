#include <system/drivers/usb/usbdevice.hpp>
#include <alinix/types.h>

class USBController;
class USBDevice;

class USBDevice{
    public:
        uint8_t portNum = 0;
        uint8_t devAddress = 0;
    // Which controller is this device attached to?
        USBController* controller = 0;
    // The name of this device present in the string descriptor
        char* deviceName = 0;
        // Class code of this device
        uint16_t classID = 0;
        // Sub-Class code of this device
        uint16_t subclassID = 0;
        // Protocol used
        uint16_t protocol = 0;
        // Vendor ID of device
        uint16_t vendorID = 0;
        // Product ID of device
        uint16_t productID = 0;

        // Driver associated with this device, 0 if none found
        USBDevice* driver = 0;

        //// Properties per controller
        struct UHCIProperties
        {
            bool lowSpeedDevice;
            int maxPacketSize;
        } uhciProperties;
        struct OHCIProperties
        {
            int desc_mps;
            bool ls_device;
        } ohciProperties;

        // List of all endpoints of device

        // Pointer to HID descriptor found in interface
        // Only valid for mouse or keyboard
        uint8_t* hidDescriptor = 0;
    
    public:
        USBDevice();
        ~USBDevice();

        bool AssignDriver();

            // Called when device is unplugged from system
        void OnUnplugged();
};