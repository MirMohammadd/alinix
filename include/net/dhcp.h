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
#ifndef __ALINIX_KERNEL_NET_DHCP_H
#define __ALINIX_KERNEL_NET_DHCP_H

#include <net/opt.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



//////////////////
// Define Useful macros fir DHCP


/** period (in seconds) of the application calling dhcp_coarse_tmr() */
#define DHCP_COARSE_TIMER_SECS 60 


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif