/**
 * @file mod_devicetable.h
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 * 	- Bluetooth header file for ath3k.c.
*/


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