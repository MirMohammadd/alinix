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

#ifndef _STATUS_H_
#define _STATUS_H_

/**
 * @file status.h
 * @author Konstantin Tcholokachvili
 * @date 2007, 2011, 2013
 * @license MIT License
 * 
 * Values which are returned from kernel functions
 */
 
 
#define KERNEL_OK                           0   
#define KERNEL_INVALID_VALUE                1   
#define KERNEL_OPERATION_NOT_SUPPORTED      2   
#define KERNEL_NO_MEMORY                    3
#define KERNEL_BUSY                         4
#define KERNEL_INTERRUPTED                  5	
#define KERNEL_PERMISSION_ERROR             6
#define KERNEL_UNRESOLVED_VIRTUAL_ADDRESS   7
#define KERNEL_INTERNAL_FATAL_ERROR         255 

#endif // _STATUS_H_
