#ifndef __ALINIX_KERNEL_HRT_TIMER_TYPES_H
#define __ALINIX_KERNEL_HRT_TIMER_TYPES_H


#include <alinix/types.h>
#include <alinix/timerqueue_types.h>

struct hrtimer {
	struct timerqueue_node		node;
	ktime_t				_softexpires;
	enum hrtimer_restart		(*function)(struct hrtimer *);
	struct hrtimer_clock_base	*base;
	uint8_t				state;
	uint8_t				is_rel;
	uint8_t				is_soft;
	uint8_t				is_hard;
};

#endif