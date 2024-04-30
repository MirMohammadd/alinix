#ifndef __UPAPI_CONNECTOR_H
#define __UPAPI_CONNECTOR_H

#include <alinix/kernel.h>

#define CN_IDX_PROC			0x1
#define CN_VAL_PROC			0x1
#define CN_IDX_CIFS			0x2
#define CN_VAL_CIFS                     0x1
#define CN_W1_IDX			0x3	/* w1 communication */
#define CN_W1_VAL			0x1
#define CN_IDX_V86D			0x4
#define CN_VAL_V86D_UVESAFB		0x1
#define CN_IDX_BB			0x5	/* BlackBoard, from the TSP GPL sampling framework */
#define CN_DST_IDX			0x6
#define CN_DST_VAL			0x1
#define CN_IDX_DM			0x7	/* Device Mapper */
#define CN_VAL_DM_USERSPACE_LOG		0x1
#define CN_IDX_DRBD			0x8
#define CN_VAL_DRBD			0x1
#define CN_KVP_IDX			0x9	/* HyperV KVP */
#define CN_KVP_VAL			0x1	/* queries from the kernel */
#define CN_VSS_IDX			0xA     /* HyperV VSS */
#define CN_VSS_VAL			0x1     /* queries from the kernel */



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