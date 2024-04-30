#ifndef __ALINIX_KERNEL_K_TIME_H
#define __ALINIX_KERNEL_K_TIME_H

#include <alinix/types.h>
#include <alinix/compiler.h>

#define PSEC_PER_NSEC			1000L


#define NSEC_PER_SEC	1000000000L
/* Located here for timespec[64]_valid_strict */
#define TIME64_MAX			((sint64_t)~((u64)1 << 63))
#define TIME64_MIN			(-TIME64_MAX - 1)

#define KTIME_MAX			((sint64_t)~((u64)1 << 63))
#define KTIME_MIN			(-KTIME_MAX - 1)
#define KTIME_SEC_MAX			(KTIME_MAX / NSEC_PER_SEC)
#define KTIME_SEC_MIN			(KTIME_MIN / NSEC_PER_SEC)


static inline ktime_t ktime_set(const sint64_t secs, const unsigned long nsecs)
{
	if (unlikely(secs >= KTIME_SEC_MAX))
		return KTIME_MAX;

	return secs * NSEC_PER_SEC + (sint64_t)nsecs;
}


#endif // __ALINIX_KERNEL_K_TIME_H