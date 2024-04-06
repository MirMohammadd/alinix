#ifndef __HEISEN_KERNEL_USB_MASS_STORAGE_HPP
#define __HEISEN_KERNEL_USB_MASS_STORAGE_HPP

#include <types.h>

#ifdef __cplusplus
using namespace LIBHeisenKernel;
#endif

#define USB_DEVICE_MASS_STORAGE 0x080650

#define USB_MSD_NOT_ATTACHED 0
#define USB_MSD_ATTACHED 1
#define USB_MSD_INITALIZED 2

#define USB_CBW_READ 0x80
#define USB_CBW_WRITE 0x00

#define USB_MSD_REQUEST_SENSE 0x03
#define USB_MSD_INQUIRY 0x12
#define USB_MSD_READ_FORMAT_CAPACITIES 0x23
#define USB_MSD_CAPACITY 0x25
#define USB_MSD_READ_10 0x28
#define USB_MSD_WRITE_10 0x2A

struct usb_mass_storage_device {
 byte_t type;
 byte_t controller_number;
 byte_t controller_type;
 byte_t interface;
 byte_t port;
 byte_t address;
 byte_t device_speed;
 byte_t endpoint_in;
 byte_t toggle_in;
 byte_t endpoint_out;
 byte_t toggle_out;
 dword_t ehci_hub_address;
 dword_t ehci_hub_port_number;
 dword_t size_in_sectors;
 dword_t size_of_sector;
}__attribute__((packed));
struct usb_mass_storage_device usb_mass_storage_devices[10];

dword_t usb_mass_storage_cbw_memory = 0, usb_mass_storage_response_memory = 0, usb_mass_storage_csw_memory = 0;

void usb_mass_storage_initalize(byte_t device_number);
void usb_msd_create_cbw(byte_t transfer_type, byte_t command_length, dword_t transfer_length);
byte_t usb_msd_transfer_command(byte_t device_number, byte_t direction, dword_t memory, dword_t length_of_transfer);
byte_t usb_msd_send_inquiry_command(byte_t device_number);
byte_t usb_msd_send_request_sense_command(byte_t device_number);
byte_t usb_msd_send_capacity_command(byte_t device_number);
byte_t usb_msd_read(byte_t device_number, dword_t sector, byte_t number_of_sectors, dword_t memory);
byte_t usb_msd_write(byte_t device_number, dword_t sector, byte_t number_of_sectors, dword_t memory);
void usb_msd_recover_from_error(byte_t device_number);

#endif // __HEISEN_KERNEL_USB_MASS_STORAGE_HPP