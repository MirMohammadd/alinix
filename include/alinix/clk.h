#ifndef __ALINIX_KERNEL_CLK_H
#define __ALINIX_KERNEL_CLK_H

#include <alinix/types.h>

struct clk;

struct clk_ops {
	void (*enable)(struct clk *);
	void (*disable)(struct clk *);
};

struct clk {
	struct clk_ops *clk_ops;
	unsigned long rate;
	unsigned long enabled;
	u8 slot;
};

#endif // __ALINIX_KERNEL_CLK_H