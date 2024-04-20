#include <alinix/mass_storage.hpp>
#include <alinix/log.h>
#include <system/drivers/usb/usbdefs.hpp>
#include <alinix/enums.h>
#include <alinix/disk.hpp>


USBMassStorageDriver::USBMassStorageDriver(USBDevice* dev)
: USBDriver(dev, "USB Mass Storage"), Disk(0, 0, USBDisk, 0, 0, 0)
{ }