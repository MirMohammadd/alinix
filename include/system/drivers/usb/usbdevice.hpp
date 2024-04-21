#ifndef __ALINIX_KERNEL_USB_DEVICE_SYSTEM_HPP
#define __ALINIX_KERNEL_USB_DEVICE_SYSTEM_HPP

#ifndef __cplusplus
# error "This file must be compiled with C++"

#endif




#include <alinix/types.h>
#include <system/drivers/usb/usbdriver.hpp>
#include <system/drivers/usb/usbcontroller.hpp>

#include "device.hpp"

class USBDevice;
class USBDriver;

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



        class USBController
        {
        protected:
            List<InterruptTransfer_t*> interrupTransfers;            
        public:
            // What type of controller is this
            USBControllerType type;
            // Create new instance of USBController class
            USBController(USBControllerType usbType);

            // Setup this controller into the active state
            virtual void Setup();

            // Function that will get called on a periodic interval in which the controller can perform specific kinds of things.
            // One of these things is port connection change checking and updating devices if necessary.
            virtual void ControllerChecksThread();

            /////
            // USB Common functions per controller
            /////

            // Perform a bulk in operation
            virtual bool BulkIn(USBDevice* device, void* retBuffer, int len, int endP);
            // Perform a bulk out operation
            virtual bool BulkOut(USBDevice* device, void* sendBuffer, int len, int endP);

            // Perform a control in operation
            virtual bool ControlIn(USBDevice* device, void* target = 0, const int len = 0, const uint8_t requestType = 0, const uint8_t request = 0, const uint16_t valueHigh = 0, const uint16_t valueLow = 0, const uint16_t index = 0);
            // Perform a control out operation
            virtual bool ControlOut(USBDevice* device, const int len = 0, const uint8_t requestType = 0, const uint8_t request = 0, const uint16_t valueHigh = 0, const uint16_t valueLow = 0, const uint16_t index = 0);
            
            // Place a interrupt in transfer in the dedicated queue, handler will get called on completion
            virtual void InterruptIn(USBDevice* device, int len, int endP);

            /////
            // Functions that use controler specific implementations
            /////

            // Get Device descriptor of specific device
            bool GetDeviceDescriptor(struct DEVICE_DESC* dev_desc, USBDevice* device);

            // Get String descriptor of specific device
            bool GetStringDescriptor(struct STRING_DESC* stringDesc, USBDevice* device, uint16_t index, uint16_t lang = 0);
            
            // Get String descriptor of specific device
            // Returns buffer with Configuration header and additional data            
            uint8_t* GetConfigDescriptor(USBDevice* device);
            
            // Set configuration for device
            bool SetConfiguration(USBDevice* device, uint8_t config);

            // Receive devices current configuration
            int GetConfiguration(USBDevice* device);
            
            // Get maximum of Logical unit numbers, Only for Mass Storage Devices!
            int GetMaxLuns(USBDevice* device);
        };

class USBDevice
{
public:
    // Port to which this device is attached to on the controller
    // This is the physical port and not a virtual address of some sort
    // The address is stored in the properties per controller
    uint8_t portNum = 0;
    // Ranging from 0 to 127, should not be 0 after initializing
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
    USBDriver* driver = 0;

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
    List<USBEndpoint*> endpoints;

    // Pointer to HID descriptor found in interface
    // Only valid for mouse or keyboard
    uint8_t* hidDescriptor = 0;
public:
    // Create new USBDevice, only called by controllers
    USBDevice();
    // Destructor
    ~USBDevice();

    // Automaticly test this device for its specs and assign a driver if found
    bool AssignDriver();

    // Called when device is unplugged from system
    void OnUnplugged();
};

#endif /*__ALINIX_KERNEL_USB_CONTROLLER_SYSTEM_HPP*/
