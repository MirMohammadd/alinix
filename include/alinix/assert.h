#ifndef __ALINIX_KERNEL_ASSERT_H
#define __ALINIX_KERNEL_ASSERT_H

#include <alinix/kernel.h>


#define assert(condition) \
    do { \
        if (!(condition)) { \
        perror("Assertion  failed\n"); \
        } \
    } while (0)


#endif // 