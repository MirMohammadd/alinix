#ifndef __ALINIX_KERNEL_COMPLETION_H
#define __ALINIX_KERNEL_COMPLETION_H

#include <alinix/kernel.h>
#include <alinix/swait.h>


struct completion {
	unsigned int done;
	struct swait_queue_head wait;
};



#endif // __ALINIX_KERNEL_COMPLETION_H