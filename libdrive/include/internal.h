#ifndef _HEISEN_KERNEL_LIB_USB_INTERNAL_H_HEADER
#define _HEISEN_KERNEL_LIB_USB_INTERNAL_H_HEADER

#include "libusbserial.h"
#include "config.h"
#include "libusbtypes.h"
#include <stdint.h>


#define UNUSED_VAR(x) ((void)(x))

#ifndef max
#define max(a,b)     (((a) > (b) ? (a):(b))) 
#endif

#ifndef min

#define min(a,b)     (((a) < (b) ? (a):(b))) 
#endif


#include <pthread.h>


struct usbserial_endpoints{
    uint8_t in;
    uint8_t out;
    uint8_t in_if;
	uint8_t out_if;
};


struct usbserial_port
{
    const struct usbserial_driver *driver;

	unsigned int port_idx;
	struct usbserial_endpoints endp;
	
	libusb_device *usb_dev;
    libusb_device_handle *usb_dev_hdl;
    struct libusb_device_descriptor usb_dev_desc;

	struct libusb_transfer *read_transfer;
    usbserial_cb_read_fn cb_read;
    usbserial_cb_error_fn cb_read_error;
    void *cb_user_data;

	pthread_mutex_t mutex;
	volatile int read_cancel_flag;
    unsigned char read_buffer[READ_BUFFER_SIZE];

	void *driver_data;
};


#endif /*_HEISEN_KERNEL_LIB_USB_INTERNAL_H_HEADER*/