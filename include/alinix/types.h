/**
 * @author Ali Mirmohammad
 * @file types.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
#ifndef __ALINIX_KERNEL__TYPES_H_HEADER_
#define __ALINIX_KERNEL__TYPES_H_HEADER_

#include "_types.h"
#include <alinix/enums.h>


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
typedef unsigned int            paddr_t;
typedef	unsigned int	uint;		/* Sys V compatibility */
typedef unsigned char byte_t; // For  backward compatibility
//! This might run into problem (size_t)
typedef unsigned long int size_t;
#if !defined(__cplusplus)
//TODO Fix here
// typedef enum  {false = 0, true = 1} bool;
#include <stdbool.h>
#endif

#ifndef NULL
#define NULL (void *)0
#endif

int strlen(const char* str);
// bool strcmp(const char* strA, const char* strB);
// bool strncmp(const char* s1, const char* s2, int n);
int IndexOf(const char* str, char c, uint32_t skip);
bool Contains(const char* str, char c);

#if !defined(ALINIX_NULL_CPP_NULL_PTR) && defined(__cplusplus) && !defined(NULL)
#define  ALINIX_NULL_CPP_NULL ALINIX_NULL_CPP_NULL_PTR

#endif /*ALINIX_NULL_CPP_NULL_PTR*/

/*Defining the operators for the File system measures*/
// uint32_t KB(unsigned long long no) {
//     return no * 1024;
// }

// uint32_t MB(unsigned long long no) {
//     return no * KB(1024);
// }

// uint32_t GB(unsigned long long no) {
//     return no * MB(1024);
// }


////////////////////////////////////////
typedef struct 
{
    uint32_t signature;     // USBC in hexadecimal, acting as magic number
    uint32_t tag;           // Signature
    uint32_t transferLen;   // Number of bytes to transfer excluding size of CBW
    uint8_t flags;          // 7: 0=Out 1=In, 6:0=Reserved
    uint8_t lun;            // 7:4 Reserved, 3:0 Logical Unit Number
    uint8_t cmdLen;         // Length of command in next field [1-16]
    uint8_t command[16];    // Command Data
} __attribute__((packed)) CommandBlockWrapper;


typedef struct {
    void* controller; // Which controller is controlling this disk device
    uint32_t controllerIndex; // The real number for the disk on the controller
    char* identifier; // Disk Identifier
    DiskType type; // Type of disk
    uint64_t size; // Size of disk in bytes
    uint32_t numBlocks; // Number of data blocks
    uint32_t blockSize; // Size of one block of data
} Disk;



// Define data types for as macros here
#define POSITIVE unsigned int
#define NEGATIVE signed int
#define NUMBER int 
#define STRING char*
#define REAL  double
#define VOID void
#define EXTERNAL extern
#define PRIVATE static
#define CONSTANT const
#define NO_ARGS void
#define NO_RETURN VOID


/////////////////////
struct callback_head {
	struct callback_head *next;
	void (*func)(struct callback_head *head);
} __attribute__((aligned(sizeof(void *))));
#define rcu_head callback_head

#endif /*__ALINIX_KERNEL__TYPES_H_HEADER_*/