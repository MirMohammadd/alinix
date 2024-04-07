#ifndef _HEISEN_LIB_USB_KERNEL_HEADER_H
#define _HEISEN_LIB_USB_KERNEL_HEADER_H

#include "internal.h"


int usbserial_io_init_bulk_read_transfer(struct usbserial_port *port);

int usbserial_io_cancel_bulk_read_transfer(struct usbserial_port *port);

int usbserial_io_bulk_read(struct usbserial_port *port,
        void *data, size_t size, int timeout);

int usbserial_io_bulk_write(struct usbserial_port *port,
        const void *data, size_t size);

int usbserial_io_get_endpoint(struct usbserial_port *port, uint8_t classs);

int usbserial_io_free_endpoint(struct usbserial_port *port);

#endif /*_HEISEN_LIB_USB_KERNEL_HEADER_H*/