#ifndef __ALINIX_KERNEL_SPIN_LOCK_TYPES_H
#define __ALINIX_KERNEL_SPIN_LOCK_TYPES_H


typedef union{
    int  slock;	/* must be signed for proper  CHECK_WAITING */
}spinlock_t;

typedef spinlock_t local_lock_t;
#endif // __ALINIX_KERNEL_SPIN_LOCK_TYPES_H