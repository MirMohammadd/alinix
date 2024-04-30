#ifndef __ALINIX_KERNEL_FIRMWARE_H
#define __ALINIX_KERNEL_FIRMWARE_H


#include <alinix/types.h>

struct firmware {
	size_t size;
	const u8 *data;

	/* firmware loader private fields */
	void *priv;
};

#endif // __ALINIX_KERNEL_FIRMWARE_H