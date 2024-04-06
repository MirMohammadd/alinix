#ifndef __HEISEN_KERNEL_USB_HUB_HPP_
#define __HEISEN_KERNEL_USB_HUB_HPP_

#include <types.h>
#ifdef __cplusplus

using namespace LIBHeisenKernel;

#endif


struct usb_hub {
 byte_t controller_type;
 byte_t controller_number;
 byte_t port;
 byte_t address;
 byte_t device_speed;
 byte_t number_of_ports;
 dword_t ehci_hub_address;
 dword_t ehci_hub_port_number;
 byte_t ports_state[8];
 byte_t ports_device_speed[8];
}__attribute__((packed));
struct usb_hub usb_hubs[10];

dword_t usb_hub_transfer_setup_packets_mem = 0, usb_hub_transfer_data_mem = 0;

byte_t usb_read_hub_number_of_port(byte_t controller_number, byte_t device_address, byte_t device_speed);
dword_t usb_hub_read_port_status(byte_t controller_number, byte_t device_address, byte_t device_speed, byte_t port);
byte_t usb_hub_is_there_some_port_connection_status_change(byte_t hub_number);
byte_t usb_hub_set_feature(byte_t controller_number, byte_t device_address, byte_t device_speed, byte_t index, byte_t value);
byte_t usb_hub_clear_feature(byte_t controller_number, byte_t device_address, byte_t device_speed, byte_t index, byte_t value);


#endif // __HEISEN_KERNEL_USB_HUB_HPP_