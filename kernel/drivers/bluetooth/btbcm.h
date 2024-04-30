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
#ifndef __ALINIX_KERNEL_BTB_CM_H
#define __ALINIX_KERNEL_BTB_CM_H

#define BCM_UART_CLOCK_48MHZ	0x01
#define BCM_UART_CLOCK_24MHZ	0x02

#include <alinix/types.h>
#include <alinix/compiler_attributes.h>
#include <alinix/compiler_types.h>

struct bcm_update_uart_baud_rate{
    u16 zero;
    u16 baud_rate;
};


struct bcm_write_uart_clock_setting{
    u8 type;
};


#endif