#ifndef _HEISEN_KERNEL_OHCI_HPP
#define _HEISEN_KERNEL_OHCI_HPP


#include <types.h>

#ifdef __cplusplus
using namespace LIBHeisenKernel;
#endif //__cplusplus

#define OHCI_SETUP (0 << 19)
#define OHCI_OUT (1 << 19)
#define OHCI_IN (2 << 19)

void initalize_ohci_controller(byte_t controller_number);
byte_t ohci_controller_detect_status_change(byte_t controller_number);
byte_t ohci_get_port_connection_status(byte_t controller_number, byte_t port_number);
byte_t ohci_get_port_connection_change_status(byte_t controller_number, byte_t port_number);
void ohci_clear_port_connection_change_status(byte_t controller_number, byte_t port_number);
byte_t ohci_enable_device_on_port(byte_t controller_number, byte_t port_number);
void ohci_set_ed(byte_t controller_number, byte_t device_speed, dword_t ed_number, dword_t address, dword_t endpoint, dword_t first_td, dword_t num_of_td);
void ohci_set_td(byte_t controller_number, dword_t td_number, dword_t next_td, dword_t attributes, dword_t toggle, dword_t buffer, dword_t buffer_length);
byte_t ohci_control_transfer(byte_t controller_number, dword_t last_td, dword_t time);
byte_t ohci_bulk_transfer(byte_t controller_number, dword_t last_td, dword_t time);
byte_t ohci_control_transfer_without_data_stage(byte_t controller_number, byte_t device_address, byte_t device_speed);
byte_t ohci_control_transfer_with_data_stage(byte_t controller_number, byte_t device_address, byte_t device_speed, word_t length);
dword_t ohci_interrupt_transfer(byte_t controller_number, byte_t device_number, byte_t device_address, byte_t device_speed, byte_t endpoint, byte_t endpoint_size, byte_t interrupt_time, dword_t memory);
byte_t ohci_send_bulk_transfer(byte_t controller_number, byte_t device_address, byte_t device_speed, dword_t transfer_type, byte_t endpoint, byte_t toggle, dword_t memory, dword_t length, dword_t time_to_wait);
byte_t ohci_bulk_out(byte_t controller_number, byte_t device_address, byte_t device_speed, byte_t endpoint, byte_t toggle, dword_t memory, dword_t length, dword_t time_to_wait);
byte_t ohci_bulk_in(byte_t controller_number, byte_t device_address, byte_t device_speed, byte_t endpoint, byte_t toggle, dword_t memory, dword_t length, dword_t time_to_wait);
byte_t ohci_hub_is_there_some_port_connection_status_change(byte_t hub_number);

#endif // _HEISEN_KERNEL_OHCI_HPP