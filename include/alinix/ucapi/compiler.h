#ifndef __ALINIX_KERNEL_DRIVERS_UCAPI_H
#define __ALINIX_KERNEL_DRIVERS_UCAPI_H

#define UACPI_ALWAYS_INLINE inline

#define UACPI_PACKED(decl)  \
    __pragma(pack(push, 1)) \
    decl;                   \
    __pragma(pack(pop))
#define uacpi_unlikely(expr) __builtin_expect(!!(expr), 0)
#define uacpi_likely(expr)   __builtin_expect(!!(expr), 1)


#endif