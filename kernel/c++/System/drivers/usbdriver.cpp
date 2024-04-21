#include <alinix/types.h>
#include <system/drivers/driver.hpp>
#include <system/drivers/usb/usbdriver.hpp>

USBDriver::USBDriver(USBDevice* dev, char* driverName)
: Driver(driverName)
{
    this->device = dev;
}