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

#include <alinix/dim.h>
#include <alinix/kernel.h>
#include <alinix/math.h>


bool dim_on_top(struct dim *dim){
    switch(dim->tune_state){
	case DIM_PARKING_ON_TOP:
	case DIM_PARKING_TIRED:
		return true;
	case DIM_GOING_RIGHT:
		return (dim->steps_left > 1) && (dim->steps_right == 1);
	default: /* DIM_GOING_LEFT */
		return (dim->steps_right > 1) && (dim->steps_left == 1);
    }
}

void dim_turn(struct dim* dim){
    	switch (dim->tune_state) {
	case DIM_PARKING_ON_TOP:
	case DIM_PARKING_TIRED:
		break;
	case DIM_GOING_RIGHT:
		dim->tune_state = DIM_GOING_LEFT;
		dim->steps_left = 0;
		break;
	case DIM_GOING_LEFT:
		dim->tune_state = DIM_GOING_RIGHT;
		dim->steps_right = 0;
		break;
	}
}


void dim_park_on_top(struct dim *dim)
{
	dim->steps_right  = 0;
	dim->steps_left   = 0;
	dim->tired        = 0;
	dim->tune_state   = DIM_PARKING_ON_TOP;
}

void dim_park_tired(struct dim *dim)
{
	dim->steps_right  = 0;
	dim->steps_left   = 0;
	dim->tune_state   = DIM_PARKING_TIRED;
}

// bool dim_calc_stats(struct dim_sample *start, struct dim_sample *end,
// 		    struct dim_stats *curr_stats)
// {
// 	/* u32 holds up to 71 minutes, should be enough */
//     u32 delta_us = ktime_us_delta(end->time, start->time);
//         u32 npkts = BIT_GAP(u32, end->pkt_ctr, start->pkt_ctr);
//         u32 nbytes = BIT_GAP(u32, end->byte_ctr, start->byte_ctr);
//         u32 ncomps = BIT_GAP(u32, end->comp_ctr, start->comp_ctr);


// 	if (!delta_us)
// 		return false;

// 	curr_stats->ppms = DIV_ROUND_UP(npkts * USEC_PER_MSEC, delta_us);
// 	curr_stats->bpms = DIV_ROUND_UP(nbytes * USEC_PER_MSEC, delta_us);
// 	curr_stats->epms = DIV_ROUND_UP(DIM_NEVENTS * USEC_PER_MSEC,
// 					delta_us);
// 	curr_stats->cpms = DIV_ROUND_UP(ncomps * USEC_PER_MSEC, delta_us);
// 	if (curr_stats->epms != 0)
// 		curr_stats->cpe_ratio = DIV_ROUND_DOWN_UP(
// 			curr_stats->cpms * 100, curr_stats->epms);
// 	else
// 		curr_stats->cpe_ratio = 0;

// 	return true;
// }