#ifndef __ALINIX_KERNEL_BUILD_BUG_H
#define __ALINIX_KERNEL_BUILD_BUG_H


#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#endif // __ALINIX_KERNEL_BUILD_BUG_H