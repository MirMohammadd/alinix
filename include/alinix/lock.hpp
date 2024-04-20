#ifndef __ALINIX_KERNEL_LOCK_HPP
#define __ALINIX_KERNEL_LOCK_HPP


class MutexLock
{
private:
    int value = 0;
public:
    MutexLock();

    void Lock();
    void Unlock();
};

#endif