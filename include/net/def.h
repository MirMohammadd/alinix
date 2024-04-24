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
#ifndef __ALINIX_KERNEL_DEF_H_INCLUDED_NET
#define __ALINIX_KERNEL_DEF_H_INCLUDED_NET


#include <alinix/types.h>



uint16_t  lwip_htons(uint16_t x);
uint16_t lwip_ntohs(uint16_t x);
// uint32_t lwip_htonl(uint32_t x);
#define lwip_htonl(x) (x)
uint32_t lwip_ntohl(uint32_t x);

#define htonl(x) lwip_htonl(x)

#define ntohl(x) lwip_ntohl(x)
#define htons(x) lwip_htons(x)












#define LWIP_MAX(x , y)  (((x) > (y)) ? (x) : (y))
#define LWIP_MIN(x , y)  (((x) < (y)) ? (x) : (y))

#endif