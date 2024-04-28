/**
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
#ifndef __ALINIX_KERNEL_DIM_H
#define __ALINIX_KERNEL_DIM_H

#include <alinix/kernel.h>
#include <alinix/math.h>
#include <alinix/uapi/const.h>

#define DIM_NEVENTS 64

#define IS_SIGNIFICANT_DIFF(val, ref) \
	((ref) && (((100UL * abs((val) - (ref))) / (ref)) > 10))
#define BIT_GAP(bits, end, start) ((((end) - (start)) + BIT_ULL(bits)) \
		& (BIT_ULL(bits) - 1))


struct dim_cq_moder{
	uint8_t usec;
	uint16_t pkts;
	uint16_t comps;
	uint8_t dim_cq_moder;
};


struct dim_sample{
	ktime_t time;
	uint32_t pkt_ctr;
	uint32_t byte_ctr;
	uint16_t event_ctr;
	uint32_t comp_ctr;
};




#endif /*__ALINIX_KERNEL_DIM_H*/