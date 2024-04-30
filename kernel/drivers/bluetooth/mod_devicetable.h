#ifndef __ALINIX_KERNEL_DRIVERS_DEVICE_TABLE_BLUE_H
#define __ALINIX_KERNEL_DRIVERS_DEVICE_TABLE_BLUE_H

#include <alinix/types.h>

struct usb_device_id {
	/* which fields to match against? */
	u16		match_flags;

	/* Used for product specific matches; range is inclusive */
	u16		idVendor;
	u16		idProduct;
	u16		bcdDevice_lo;
	u16		bcdDevice_hi;

	/* Used for device class matches */
	u8		bDeviceClass;
	u8		bDeviceSubClass;
	u8		bDeviceProtocol;

	/* Used for interface class matches */
	u8		bInterfaceClass;
	u8		bInterfaceSubClass;
	u8		bInterfaceProtocol;

	/* Used for vendor-specific interface matches */
	u8		bInterfaceNumber;

	/* not matched against */
	unsigned long	driver_info
		__attribute__((aligned(sizeof(unsigned long))));
};

#endif // __ALINIX_KERNEL_DRIVERS_DEVICE_TABLE_BLUE_H