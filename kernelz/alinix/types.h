#ifndef __ALINIX_KERNEL__TYPES_H_HEADER
#define __ALINIX_KERNEL__TYPES_H_HEADER_

#include "_types.h"


typedef char                        int8_t;
typedef unsigned char               uint8_t;
typedef short                       int16_t;
typedef unsigned short              uint16_t;
typedef int                         int32_t;
typedef unsigned int                uint32_t;
typedef long long int               int64_t;
typedef unsigned long long int      uint64_t;
typedef unsigned long long          uintptr_t;
typedef signed char               sint8_t;
typedef signed short              sint16_t;
typedef signed int               sint32_t;
typedef signed long long int      sint64_t;
#if !defined(__cplusplus)
#define bool unsigned char
#define true 1
#define false 0
#endif

#ifndef NULL
#define NULL ALINIX_NULL
#endif

#if !defined(ALINIX_NULL_CPP_NULL_PTR) && defined(__cplusplus)
#define  ALINIX_NULL_CPP_NULL ALINIX_NULL_CPP_NULL_PTR

#endif /*ALINIX_NULL_CPP_NULL_PTR*/


#endif /*__ALINIX_KERNEL__TYPES_H_HEADER_*/