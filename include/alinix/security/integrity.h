#ifndef __ALINIX_KERNEL_SECURITY_M_H
#define __ALINIX_KERNEL_SECURITY_M_H

#include <alinix/types.h>

#define IMA_MAX_DIGEST_SIZE	1024

struct ima_digest_data {
	u8 algo;
	u8 length;
	union {
		struct {
			u8 unused;
			u8 type;
		} sha1;
		struct {
			u8 type;
			u8 algo;
		} ng;
		u8 data[2];
	} xattr;
	u8 digest[];
} __packed;


#endif