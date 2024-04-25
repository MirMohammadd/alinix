/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __ALINIX_KERNEL_COMPILER_H
#define __ALINIX_KERNEL_COMPILER_H

#include <alinix/types.h>
#include <net/typing.h>

/**
 * @brief Define the compiler  macro to mark something as deprecated.
*/
#if defined(__clang__)
    #define USING_CLANG 1

#elif defined(__GNUC__)
    #define USING_GCC 1

#elif defined(_MSC_VER)
    #define USING_MSC_VER 1

#elif defined(__GNUC__) && defined(__ELF__) && defined(__x86_64__)
    #define USING_ELF_GCC_TOOLCHAIN_X86_64 1

#endif


/* Compiler hints for packing structures */
#define PACK_STRUCT_FIELD(x) x
// #define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END
#ifdef LWIP_UNIX_EMPTY_ASSERT
#define LWIP_PLATFORM_ASSERT(x)
#else
#define LWIP_PLATFORM_ASSERT(x) do {printf("Assertion \"%s\" failed at line %d in %s\n", \
                                     x, __LINE__, __FILE__);} while(0)
#endif

#define LWIP_RAND() ((uint32_t)rand())



typedef uintptr_t  mem_ptr_t;


#endif /*__ALINIX_KERNEL_COMPILER_H*/