#ifndef _HEISEN_KERNEL_DRIVER_H_HEADER_LIB_USB_HEADER
#define _HEISEN_KERNEL_DRIVER_H_HEADER_LIB_USB_HEADER

#include "libusbserial.h"

struct usbserial_driver
{
    int (*check_supported_by_vid_pid)(uint16_t vid, uint16_t pid);
    int (*check_supported_by_class)(
            uint8_t class,
            uint8_t subclass);
    const char* (*get_device_name)(
            uint16_t vid,
            uint16_t pid,
            uint8_t classs,
            uint8_t subclass);
    unsigned int (*get_ports_count)(uint16_t vid, uint16_t pid);

    int (*port_init)(struct usbserial_port *port);
    int (*port_deinit)(struct usbserial_port *port);

    int (*port_set_config)(
            struct usbserial_port *port,
            const struct usbserial_config* config);

    int (*start_reader)(struct usbserial_port *port);
    int (*stop_reader)(struct usbserial_port *port);

    int (*read)(
            struct usbserial_port *port,
            void *data,
            size_t size,
			int timeout);
    int (*write)(
            struct usbserial_port *port,
            const void *data,
            size_t size);
    int (*purge)(
            struct usbserial_port *port,
            int rx,
            int tx);

    void (*read_data_process)(
            struct usbserial_port *port,
            void *data,
            size_t *size);
			
	int (*set_dtr_rts)(
            struct usbserial_port *port,
            int dtr,
            int rts);
};

#endif /*_HEISEN_KERNEL_DRIVER_H_HEADER_LIB_USB_HEADER*/