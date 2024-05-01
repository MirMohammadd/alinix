#ifndef _ALINIX_KERNEL_DESC_H
#define _ALINIX_KERNEL_DESC_H

#include <alinix/types.h>

struct gpio_desc {
	unsigned	valid		: 1;
	unsigned	can_wakeup	: 1;
	unsigned	keypad_gpio	: 1;
	unsigned	dir_inverted	: 1;
	unsigned int	mask; /* bit mask in PWER or PKWR */
	unsigned int	mux_mask; /* bit mask of muxed gpio bits, 0 if no mux */
	unsigned long	config;
};

#endif