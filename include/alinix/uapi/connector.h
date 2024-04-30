#ifndef __UPAPI_CONNECTOR_H
#define __UPAPI_CONNECTOR_H

#include <alinix/kernel.h>

struct cb_id {
	u32 idx;
	u32 val;
};

struct cn_msg {
	struct cb_id id;

	u32 seq;
	u32 ack;

	u16 len;		/* Length of the following data */
	u16 flags;
	u8 data[];
};


#endif