#pragma once

#include <types.h>

#ifdef __cplusplus
using namespace LIBHeisenKernel;
#endif // __cplusplus

#define EHCI_NO_POINTER 0x1

#define EHCI_SETUP 0x2
#define EHCI_IN 0x1
#define EHCI_OUT 0x0

byte_t ehci_hub_address = 0, ehci_hub_port_number = 0;

void initalize_ehci_controller(byte_t controller_number);
byte_t ehci_controller_detect_status_change(byte_t controller_number);
byte_t ehci_get_port_connection_status(byte_t controller_number, byte_t port_number);
byte_t ehci_get_port_connection_change_status(byte_t controller_number, byte_t port_number);
void ehci_clear_port_connection_change_status(byte_t controller_number, byte_t port_number);
byte_t ehci_enable_device_on_port(byte_t controller_number, byte_t port_number);
void ehci_set_qh(byte_t controller_number, dword_t qh_number, dword_t first_td, dword_t device_address, dword_t device_speed, dword_t endpoint);
void ehci_set_td(byte_t controller_number, dword_t td_number, dword_t next_td_number, dword_t packet_type, dword_t length, dword_t toggle, dword_t memory);
byte_t ehci_control_or_bulk_transfer(byte_t controller_number, byte_t last_descriptor, dword_t time);
byte_t ehci_control_transfer_without_data_stage(byte_t controller_number, byte_t device_address, byte_t device_speed);
byte_t ehci_control_transfer_with_data_stage(byte_t controller_number, byte_t device_address, byte_t device_speed, word_t length);
dword_t ehci_interrupt_transfer(byte_t controller_number, byte_t device_number, byte_t device_address, byte_t device_speed, byte_t endpoint, byte_t endpoint_size, byte_t interrupt_time, dword_t memory);
byte_t ehci_bulk_transfer(byte_t controller_number, byte_t device_address, byte_t device_speed, byte_t transfer_type, byte_t endpoint, byte_t toggle, dword_t memory, dword_t length, dword_t time_to_wait);
byte_t ehci_bulk_out(byte_t controller_number, byte_t device_address, byte_t device_speed, byte_t endpoint, byte_t toggle, dword_t memory, dword_t length, dword_t time_to_wait);
byte_t ehci_bulk_in(byte_t controller_number, byte_t device_address, byte_t device_speed, byte_t endpoint, byte_t toggle, dword_t memory, dword_t length, dword_t time_to_wait);
byte_t ehci_hub_is_there_some_port_connection_status_change(byte_t hub_number);