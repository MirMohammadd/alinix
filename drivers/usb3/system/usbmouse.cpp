// #include <system/drivers/usb/usbmouse.h>
// #include <system/drivers/usb/usbdefs.h>
// #include <system/log.h>
// #include <system/system.h>
// #include <system/usb/hidparser.h>


#include <system/drivers/usb/usbmouse.hpp>
#include <system/drivers/usb/usbdevice.hpp>
#include <system/drivers/usb/usbendpoint.hpp>
#include <alinix/memory.h>
#include <alinix/systeminfo.h>
#include <alinix/stream.hpp>
#include <alinix/system.hpp>



USBMouse::USBMouse(USBDevice* dev)
: USBDriver(dev, "USB HID Mouse")
{ }

bool USBMouse::GetHIDProperty(struct HID_DATA* target, uint8_t* buffer, int bufLen, HID_USAGE item)
{
    memset(target, 0, sizeof(struct HID_DATA));
    target->type = ITEM_INPUT;
    target->path.node[0].u_page = HID_PAGE_USAGE::GEN_DESKTOP;
    target->path.node[0].usage = HID_USAGE::MOUSE;
    target->path.node[1].u_page = HID_PAGE_USAGE::GEN_DESKTOP;
    target->path.node[1].usage = HID_USAGE::POINTER;
    target->path.node[2].u_page = HID_PAGE_USAGE::GEN_DESKTOP;
    target->path.node[2].usage = item;
    target->path.size = 3;
    
    this->hidParser.report_desc = (const uint8_t*)buffer;
    this->hidParser.report_desc_size = bufLen;

    return this->hidParser.FindObject(target);
}

bool USBMouse::Initialize()
{
    if(this->device->hidDescriptor == 0)
        return false;

    // Find Interrupt Endpoint
    for(USBEndpoint* ep : this->device->endpoints) {
        if(ep->type == EndpointType::Interrupt) { // Interrupt Endpoint
            if(ep->dir == EndpointDirection::In) { // In
                this->InInterruptEndpoint = ep->endpointNumber;
                break;
            }
        }
    }

    // Check if endpoint is found
    if(this->InInterruptEndpoint == -1)
        return false;

    // Send set-idle request to device
    if(!this->device->controller->ControlOut(this->device, 0, HOST_TO_DEV | REQ_TYPE_CLASS | RECPT_INTERFACE, HID_REQUEST_SET_IDLE))
        Log(Warning, "USBMouse not reacting to SetIdle request");
    
    // Get length of HID report from Interface HID Descriptor
    uint16_t reportDescriptorLength = *(uint16_t*)(this->device->hidDescriptor + sizeof(IF_HID_DESC) + 1);
    if(reportDescriptorLength == 0)
        return false;

    // Receive Report Descriptor
    uint8_t* reportDescriptorBuffer = new uint8_t[reportDescriptorLength];
    if(!this->device->controller->ControlIn(this->device, reportDescriptorBuffer, reportDescriptorLength, DEV_TO_HOST | REQ_TYPE_STNDRD | RECPT_INTERFACE, GET_DESCRIPTOR, 0x22))
        return false;
    
    // Extract data returned from descriptor
    bool b1 = GetHIDProperty(&this->hidX, reportDescriptorBuffer, reportDescriptorLength, HID_USAGE::POINTER_X);
    bool b2 = GetHIDProperty(&this->hidY, reportDescriptorBuffer, reportDescriptorLength, HID_USAGE::POINTER_Y);
    bool b3 = GetHIDProperty(&this->hidZ, reportDescriptorBuffer, reportDescriptorLength, HID_USAGE::POINTER_WHEEL);
    
    // Since all required data is present from the discriptor we can use the custom protocol
    if(b1 && b2 && b3)
        this->useCustomReport = true;

    // Send SET_PROTOCOL request to device
    if(!this->device->controller->ControlOut(this->device, 0, HOST_TO_DEV | REQ_TYPE_CLASS | RECPT_INTERFACE, HID_REQUEST_SET_PROTOCOL, 0, this->useCustomReport ? 1 : 0))
        return false;

    // Start recieving interrupt packets from device
    this->device->controller->InterruptIn(this->device, 4, this->InInterruptEndpoint);

    return true;
}

void USBMouse::DeInitialize()
{ } // Mouse does not have any requirements for unplugging

bool USBMouse::HandleInterruptPacket(InterruptTransfer_t* transfer)
{
    uint8_t* packet = transfer->bufferPointer;
    //Log(Info, "Received mouse packet! %d %d %d %d", packet[0], (int8_t)packet[1], (int8_t)packet[2], packet[3]);
    
    // Process buttons first, this is the same (we assume) for all mouse devices
    systemInfo->MouseLeftButton = packet[0] & (1<<0);
    systemInfo->MouseRightButton = packet[0] & (1<<1);
    systemInfo->MouseMiddleButton = packet[0] & (1<<2);

    int realX = 0;
    int realY = 0;
    
    // Then process XYZ information
    if(this->useCustomReport) {
        realX = (int8_t)(packet[this->hidX.offset / 8]);
        realY = (int8_t)(packet[this->hidY.offset / 8]);
        systemInfo->MouseZ += (int8_t)(packet[this->hidZ.offset / 8]);
    }
    else {
        realX = (int8_t)(packet[1]);
        realY = (int8_t)(packet[2]);
        systemInfo->MouseZ += (int8_t)(packet[3]);
    }

    // Boundry checking for desktop

    int newX = (systemInfo->MouseX + realX);
    if((newX >= 0) && (newX < (int)gfxDevice->width))
        systemInfo->MouseX = newX;
    else if(newX < 0)
        systemInfo->MouseX = 0;
    else if(newX >= (int)gfxDevice->width)
        systemInfo->MouseX = gfxDevice->width - 1;
    
    int newY = (systemInfo->MouseY + realY);
    if((newY >= 0) && (newY < (int)gfxDevice->height))
        systemInfo->MouseY = newY;
    else if(newY < 0)
        systemInfo->MouseY = 0;
    else if(newY >= (int)gfxDevice->height)
        systemInfo->MouseY = gfxDevice->height - 1;
    
    return true; // Rescedule
}