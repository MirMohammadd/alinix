#ifndef _HEISEN_KERNEL_USB_TYPES_H
#define _HEISEN_KERNEL_USB_TYPES_H

// typedef char                        int8_t;
typedef unsigned char               uint8_t;
typedef short                       int16_t;
typedef unsigned short              uint16_t;
typedef int                         int32_t;
typedef unsigned int                uint32_t;
typedef long long int               int64_t;
typedef unsigned long long int      uint64_t;
// typedef unsigned long long          uintptr_t;
#if !defined(__cplusplus)
typedef enum { false = 0, true = 1 } bool;
#endif


#endif /*_HEISEN_KERNEL_USB_TYPES_H*/