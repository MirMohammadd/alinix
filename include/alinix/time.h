#ifndef __ALINIX_KERNEL_TIME_H
#define __ALINIX_KERNEL_TIME_H

#include <alinix/types.h>

struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};

struct timespec64 {
	sint64_t	tv_sec;			/* seconds */
	long		tv_nsec;		/* nanoseconds */
};

#endif // __ALINIX_KERNEL_TIME_H