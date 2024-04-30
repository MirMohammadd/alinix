#ifndef __ALINIX_KERNEL_JIFFIES_H
#define __ALINIX_KERNEL_JIFFIES_H

#include <alinix/types.h>
#include <alinix/limits.h>

#define MSEC_PER_SEC	1000L
#define USEC_PER_MSEC	1000L
#define NSEC_PER_USEC	1000L
#define NSEC_PER_MSEC	1000000L
#define USEC_PER_SEC	1000000L
#define NSEC_PER_SEC	1000000000L
#define PSEC_PER_SEC	1000000000000LL
#define FSEC_PER_SEC	1000000000000000LL
#define HZ 1000


#define MAX_JIFFY_OFFSET ((LONG_MAX >> 1)-1)

static inline unsigned long _msecs_to_jiffies(const unsigned int m)
{
	return (m + (MSEC_PER_SEC / HZ) - 1) / (MSEC_PER_SEC / HZ);
}

static __always_inline unsigned long msecs_to_jiffies(const unsigned int m)
{
	if (m) {
		if ((int)m < 0)
			return MAX_JIFFY_OFFSET;
		return _msecs_to_jiffies(m);
	} else {
		return __msecs_to_jiffies(m);
	}
}



#endif // __ALINIX_KERNEL_JIFFIES_H