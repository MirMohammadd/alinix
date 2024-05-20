/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/


/**
 * @abstraction:
 *  - Kernel system driver for C++
*/

// #include <system/drivers/usb/usbcontroller.hpp>
// #include <system/drivers/usb/usbcontroller.hpp>
// #include <system/drivers/usb/usbdefs.hpp>
// // #include <system/system.h>
// #include <alinix/log.h>
// #include <alinix/memory.h>





// USBController::USBController(USBControllerType usbType)
// {
//     this->type = usbType;
//     // this->interrupTransfers.Clear();
// }

// void USBController::Setup()
// {
//     Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
// }
// void USBController::ControllerChecksThread()
// {
//     Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
// }

// //////////////
// // Controller specific transfer functions
// //////////////

// bool USBController::BulkIn(USBDevice* device, void* retBuffer, int len, int endP)
// {
//     Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
//     return false;
// }
// bool USBController::BulkOut(USBDevice* device, void* sendBuffer, int len, int endP)
// {
//     Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
//     return false;
// }
// bool USBController::ControlIn(USBDevice* device, void* target, const int len, const uint8_t requestType, const uint8_t request, const uint16_t valueHigh, const uint16_t valueLow, const uint16_t index)
// {
//     Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
//     return false;
// }
// bool USBController::ControlOut(USBDevice* device, const int len, const uint8_t requestType, const uint8_t request, const uint16_t valueHigh, const uint16_t valueLow, const uint16_t index)
// {
//     Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
//     return false;
// }
// void USBController::InterruptIn(USBDevice* device, int len, int endP)
// {
//     Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
// }


// /////////////
// // Specific Functions independent of controller
// /////////////


// bool USBController::GetDeviceDescriptor(struct DEVICE_DESC* dev_desc, USBDevice* device)
// {
//     return ControlIn(device, dev_desc, sizeof(struct DEVICE_DESC), STDRD_GET_REQUEST, DeviceRequest::GET_DESCRIPTOR, DescriptorTypes::DEVICE);
// }

// bool USBController::GetStringDescriptor(struct STRING_DESC* stringDesc, USBDevice* device, uint16_t index, uint16_t lang)
// {
//     if(!ControlIn(device, stringDesc, 2, STDRD_GET_REQUEST, DeviceRequest::GET_DESCRIPTOR, DescriptorTypes::STRING, index, lang))
//         return false;
        
//     int totalSize = stringDesc->len;
//     return ControlIn(device, stringDesc, totalSize, STDRD_GET_REQUEST, DeviceRequest::GET_DESCRIPTOR, DescriptorTypes::STRING, index, lang);
// }

// uint8_t* USBController::GetConfigDescriptor(USBDevice* device)
// {
//     struct CONFIG_DESC confDesc;
//     memset(&confDesc, 0, sizeof(struct CONFIG_DESC));

//     if(!ControlIn(device, &confDesc, sizeof(struct CONFIG_DESC), STDRD_GET_REQUEST, GET_DESCRIPTOR, CONFIG))
//         return 0;
    
//     int totalSize = confDesc.tot_len;
//     uint8_t* buffer = new uint8_t[totalSize];
//     memset(buffer, 0, totalSize);

//     if(!ControlIn(device, buffer, totalSize, STDRD_GET_REQUEST, GET_DESCRIPTOR, CONFIG))
//         return 0;
    
//     return buffer;
// }

// bool USBController::SetConfiguration(USBDevice* device, uint8_t config)
// {
//     return ControlOut(device, 0, STDRD_SET_REQUEST, SET_CONFIGURATION, 0, config);
// }

// int USBController::GetConfiguration(USBDevice* device)
// {
//     uint8_t ret = 0;
//     if(!ControlIn(device, &ret, 1, STDRD_GET_REQUEST, GET_CONFIGURATION))
//         return 0;
    
//     return ret;
// }

// int USBController::GetMaxLuns(USBDevice* device)
// {
//     uint8_t ret = 0;
//     for(int i = 0; i < 3; i++) {
//         if(ControlIn(device, &ret, 1, DEV_TO_HOST | REQ_TYPE_CLASS | RECPT_INTERFACE, GET_MAX_LUNS))
//             return ret;
        
//         // If request failed send Clear feature (HALT) to control endpoint
//         device->controller->ControlOut(device, 0, HOST_TO_DEV | REQ_TYPE_STNDRD | RECPT_ENDPOINT, CLEAR_FEATURE);
//     }
//     return 0;
// }