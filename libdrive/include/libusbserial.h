#ifndef _HEISEN_KERNEL_LIB_USB_SER_HEADER_H__
#define _HEISEN_KERNEL_LIB_USB_SER_HEADER_H__

#include "libusb.h"
#include "libusbtypes.h"

struct usbserial_port;

typedef void (*usbserial_cb_read_fn)(void *data, size_t size, void *user_data);
typedef void (*usbserial_cb_error_fn)(enum libusb_transfer_status status, void *user_data);

enum usbserial_data_bits{
    USBSERIAL_DATABITS_5 = 5,
    USBSERIAL_DATABITS_6 = 6,
    USBSERIAL_DATABITS_7 = 7,
    USBSERIAL_DATABITS_8 = 8
};

enum usbserial_stop_bits{
    USBSERIAL_STOPBITS_1,
    USBSERIAL_STOPBITS_1_5,
    USBSERIAL_STOPBITS_2
};

enum usb_serial_parity{
    USB_SERIAL_PARITY_NONE,
    USB_PARITY_ODD,
    USB_PARITY_EVEN,
    USB_PARITY_MARK,
    USB_PARITY_SPACE
};

struct usbserial_config{
    unsigned int baud;
    enum usbserial_data_bits databits;
    enum usbserial_stop_bits stopbits;
    enum usb_serial_parity parity;
    #if defined(__cplusplus)
    bool flow_control;
    bool auto_baud;
    #endif /*__cplusplus*/
};

/* Returns a nonzero value, if a USB device is supported by one
 * of the libusbserial drivers. */
int usbserial_is_device_supported(uint16_t vid, uint16_t pid, uint8_t classs, uint8_t subclass);
/* Get a short device name. It is guaranteed to return a valid C
 * string (not NULL), if the device is supported, see
 * usbserial_is_device_supported(). Otherwise, the results are
 * undefined. */
const char* usbserial_get_device_name(uint16_t vid, uint16_t pid, uint8_t classs, uint8_t subclass);
const char* usbserial_get_device_name2(struct usbserial_port *port);
/* Return the (expected) count of ports for a USB to Serial Adapter
 * device. If the device is not supported, see
 * usbserial_is_device_supported(), the results are undefined.
 * Never returns an error code, but might return zero if an error
 * occurs. */
unsigned int usbserial_get_ports_count(uint16_t vid, uint16_t pid, uint8_t classs, uint8_t subclass);

/* Initialize a serial port instance.
 * Returns zero on success, and an error code on failure.
 * The usbserial_port instance object is stored in *out_port.
 * It is guaranteed that *out_port is NULL if an error occured
 * (non-zero return value) and that *out_port is not NULL on
 * success (zero return value).
 * Results are undefined, if port_idx >= usbserial_get_ports_count()
 * return value.
 * cb_read must not be NULL, unless no read operations are performed
 * (usbserial_start_reader() is not called afterwards).
 * read_error_cb can be NULL, then no read error notifications are sent. */
int usbserial_port_init(struct usbserial_port **out_port,
		libusb_device_handle *usb_device_handle, unsigned int port_idx,
        usbserial_cb_read_fn cb_read, usbserial_cb_error_fn read_error_cb, void* cb_user_data);
/* Deinitialize / invalidate a serial port instance.
 * Returns zero on success, and an error code on failure.
 * Results are undefined, if usbserial_stop_reader() was
 * not called before, unless usbserial_start_reader() was
 * not called. */
int usbserial_port_deinit(struct usbserial_port *port);

/* Set the line configuration (including baud rate) for a
 * serial port instance.
 * Returns zero on success, and an error code on failure. */
int usbserial_port_set_config(struct usbserial_port *port, const struct usbserial_config *config);

/* Start reading from the port.
 * Returns zero on success, and an error code on failure. */
int usbserial_start_reader(struct usbserial_port *port);
/* Stop reading from the port.
 * Returns zero on success, and an error code on failure.
 * This function must not be called from the same thread in which
 * the libusb events are handled! */
int usbserial_stop_reader(struct usbserial_port *port);

/* Synchronously read data from a port.
 * Returns zero on success, and an error code on failure. */
int usbserial_read(struct usbserial_port *port, void *data, size_t size, int timeout);
/* Synchronously write data to a port.
 * Returns zero on success, and an error code on failure. */
int usbserial_write(struct usbserial_port *port, const void *data, size_t size);

/* Purge the hardware read (rx) / (tx) buffer.
 * Returns zero on success, and an error code on failure.
 * Not supported by all drivers / devices, returns
 * USBSERIAL_ERROR_UNSUPPORTED_OPERATION in this case. */
int usbserial_purge(struct usbserial_port *port, int rx, int tx);

/* */
int usbserial_set_dtr_rts(struct usbserial_port *port, int dtr, int rts);

/* Get the string represenation for an usbserial error code,
 * which can be a libusb error code.
 * Returns NULL, if 0 == error_code and is guaranteed to return
 * an non-NULL C string if 0 != error_code */
const char* usbserial_get_error_str(int error_code);

#define DEFINE_USBSERIAL_ERROR(num) (-1000000 - num)

#define USBSERIAL_ERROR_UNSUPPORTED_OPERATION DEFINE_USBSERIAL_ERROR(0)
#define USBSERIAL_ERROR_ILLEGAL_STATE DEFINE_USBSERIAL_ERROR(1)
#define USBSERIAL_ERROR_INVALID_PARAMETER DEFINE_USBSERIAL_ERROR(2)
#define USBSERIAL_ERROR_RESOURCE_ALLOC_FAILED DEFINE_USBSERIAL_ERROR(3)
#define USBSERIAL_ERROR_NO_SUCH_DEVICE DEFINE_USBSERIAL_ERROR(4)
#define USBSERIAL_ERROR_UNSUPPORTED_DEVICE DEFINE_USBSERIAL_ERROR(5)
#define USBSERIAL_ERROR_UNSUPPORTED_BAUD_RATE DEFINE_USBSERIAL_ERROR(6)
#define USBSERIAL_ERROR_INVALID_PORT_IDX DEFINE_USBSERIAL_ERROR(7)
#define USBSERIAL_ERROR_CTRL_CMD_FAILED DEFINE_USBSERIAL_ERROR(8)

#endif /*_HEISEN_KERNEL_LIB_USB_SER_HEADER_H__*/