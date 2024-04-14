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

#ifndef IO_H_TYPES
#define IO_H_TYPES



#ifndef NULL
#define NULL 0
#endif 


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef unsigned char           uint8_t;  
typedef unsigned long long int  uint64_t;	/**< 64 bits unsigned */
typedef unsigned long int       uint32_t; 	/**< 32 bits unsigned */
typedef unsigned short int      uint16_t; 	/**< 16 bits unsigned */
typedef unsigned char           uint8_t;  	/**< 8  bits unsigned */
typedef unsigned char           uchar_t;  	/**< 8  bits unsigned */
typedef uint8 byte;
typedef uint16 word;
typedef uint32 dword;
typedef unsigned long long uint64;
typedef long long int64;
typedef int64 qword;
typedef uint32 size_t; 
typedef signed long int         int32_t; 	/**< 32 bits signed */
typedef uint32 fd_t;

#define TRUE     1
#define FALSE 0

#define true 1
#define false 0


#endif
