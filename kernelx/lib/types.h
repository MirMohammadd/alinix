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

#ifndef _TYPES_H_
#define _TYPES_H_

/**
 * @file types.h
 * @author Konstantin Tcholokachvili
 * @date 2007, 2013
 * @license MIT License
 * 
 * Basic types definition
 */

#define NULL ((void*)0)

typedef enum { FALSE=0, TRUE } bool_t;

typedef unsigned long long int  uint64_t;	/**< 64 bits unsigned */
typedef unsigned long int       uint32_t; 	/**< 32 bits unsigned */
typedef unsigned short int      uint16_t; 	/**< 16 bits unsigned */
typedef unsigned char           uint8_t;  	/**< 8  bits unsigned */
typedef unsigned char           uchar_t;  	/**< 8  bits unsigned */

typedef signed long long int    int64_t;	/**< 64 bits signed */
typedef signed long int         int32_t; 	/**< 32 bits signed */
typedef signed short int        int16_t; 	/**< 16 bits signed */
typedef signed char             int8_t;		/**< 8  bits signed */

/** Physical address */
typedef unsigned int            paddr_t;

/** Virtual address */
typedef unsigned int            vaddr_t;

/** Memory size of an object */
typedef unsigned int            size_t;

/** Return status **/
typedef int                     ret_t;

/** Offset type */
typedef signed int              off_t;

#endif // _TYPES_H_

