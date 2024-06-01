/**
 * @author Ali Mirmohammad
 * @file alps.h
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

#ifndef __ALINIX_KERNEL_ALPS_H
#define __ALINIX_KERNEL_ALPS_H

#include <alinix/types.h>
#include "pos.h"

#define MAX_TOUCHES 4


#define ALPS_PROTO_V1		0x100
#define ALPS_PROTO_V2		0x200
#define ALPS_PROTO_V3		0x300
#define ALPS_PROTO_V3_RUSHMORE	0x310
#define ALPS_PROTO_V4		0x400
#define ALPS_PROTO_V5		0x500
#define ALPS_PROTO_V6		0x600
#define ALPS_PROTO_V7		0x700	/* t3btl t4s */
#define ALPS_PROTO_V8		0x800	/* SS4btl SS4s */
#define ALPS_PROTO_V9		0x900	/* ss3btl */

struct alps_nibble_commands{
    int command;
    unsigned char data;
};

struct alps_bitmap_point {
	int start_bit;
	int num_bits;
};

struct alps_fields {
	unsigned int x_map;
	unsigned int y_map;
	unsigned int fingers;

	int pressure;
	struct input_mt_pos st;
	struct input_mt_pos mt[MAX_TOUCHES];

	unsigned int first_mp:1;
	unsigned int is_mp:1;

	unsigned int left:1;
	unsigned int right:1;
	unsigned int middle:1;

	unsigned int ts_left:1;
	unsigned int ts_right:1;
	unsigned int ts_middle:1;
};


struct alps_protocol_info {
	u16 version;
	u8 byte0, mask0;
	unsigned int flags;
};

struct alps_model_info {
	u8 signature[3];
	struct alps_protocol_info protocol_info;
};

#endif /*__ALINIX_KERNEL_ALPS_H*/