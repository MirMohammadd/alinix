/**
 * @file bluetooth.h
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

/**
 * @abstraction:
 * 	- Bluetooth header file for ath3k.c.
*/

#ifndef __ALINIX_KERNEL_BLUE_TOOTH_H
#define __ALINIX_KERNEL_BLUE_TOOTH_H

#include <alinix/types.h>
typedef struct {
	u8 b[6];
}  bdaddr_t;


#endif /*__ALINIX_KERNEL_BLUE_TOOTH_H*/