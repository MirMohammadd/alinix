#ifndef _HEISEN_LIB_DRIVE_USB_H
#define _HEISEN_LIB_DRIVE_USB_H

#include "libusbtypes.h"
#include <semaphore.h>
#include "libusb.h"



#define PRINTER_CRASH_TIMEOUT_RECEIVE (60 * 60 * 6)
#define PRINTER_CRASH_TIMEOUT_ANSWER 5
#define CONN_STALE_THRESHHOLD 5

struct usb_interface{
    uint8_t interface_number;
    uint8_t lib_usb_interface_index;
    int interface_alt;
    uint8_t endpoint_int;
    uint8_t endpoint_out;
    sem_t lock;
};


struct usb_sock_t{
    libusb_context *context;
    libusb_device_handle *printer;
    char* device_id;
    int max_packet_size;
    uint32_t num_interfaces;
    struct usb_interface *interfaces;
    sem_t num_staled_lock;
    sem_t pool_manage_lock;
    uint32_t num_avail;
    uint32_t num_taken;

    uint32_t *interface_pool;
};


struct usb_conn_t{
    struct usb_sock_t *parent;
    struct usb_interface *interface;
    uint32_t interface_index;
    int is_staled;
};

struct usb_sock_t *usb_open(void);
void usb_close(struct usb_sock_t *);

int usb_can_callback(struct usb_sock_t *);
void usb_register_callback(struct usb_sock_t *);

struct usb_conn_t *usb_conn_acquire(struct usb_sock_t *);
void usb_conn_release(struct usb_conn_t *);

int usb_conn_packet_send(struct usb_conn_t *, struct http_packet_t *);
struct http_packet_t *usb_conn_packet_get(struct usb_conn_t *, struct http_message_t *);



#endif // _HEISEN_LIB_DRIVE_USB_H