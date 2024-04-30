#ifndef __ALINIX_KERNEL_SPIN_LOCK_H
#define __ALINIX_KERNEL_SPIN_LOCK_H

#include <alinix/kernel.h>
#include <alinix/assert.h>
#include <alinix/spinlock_types.h>


static inline void spin_lock_init(spinlock_t *lock)
{
	int r = pthread_spin_init(lock, 0);
	assert(!r);
}

static inline void spin_lock(spinlock_t *lock)
{
	int ret = pthread_spin_lock(lock);
	assert(!ret);
}

static inline void spin_unlock(spinlock_t *lock)
{
	int ret = pthread_spin_unlock(lock);
	assert(!ret);
}

static inline void spin_lock_bh(spinlock_t *lock)
{
	spin_lock(lock);
}

static inline void spin_unlock_bh(spinlock_t *lock)
{
	spin_unlock(lock);
}

static inline void spin_lock_irq(spinlock_t *lock)
{
	spin_lock(lock);
}

static inline void spin_unlock_irq(spinlock_t *lock)
{
	spin_unlock(lock);
}

static inline void spin_lock_irqsave(spinlock_t *lock, unsigned long f)
{
	spin_lock(lock);
}

static inline void spin_unlock_irqrestore(spinlock_t *lock, unsigned long f)
{
	spin_unlock(lock);
}


#endif // __ALINIX_KERNEL_SPIN_LOCK_H