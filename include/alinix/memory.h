/**
 * @author Ali Mirmohammad
 * @file memory.h
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

#ifndef _ALINIX_KERNEL_MEMORY_H
#define _ALINIX_KERNEL_MEMORY_H

#include <alinix/types.h>
#include <alinix/bytes.h>
#include <alinix/ulib.h>

void memset(void* bufptr, char value, uint32_t size);
void* memcpy(void* dstptr, const void* srcptr, uint32_t size);
int memcmp(const void* aptr, const void* bptr, uint32_t size);
void * memmove(void* dstptr, const void* srcptr, uint32_t size);

#define phys2virt(x) ((x) + THREE_GB)
#define virt2phys(x) ((x) - THREE_GB)
#define LWIP_PBUF_MEMPOOL(name, num, payload, desc) LWIP_MEMPOOL(name, num, (MEMP_ALIGN_SIZE(sizeof(struct pbuf)) + MEMP_ALIGN_SIZE(payload)), desc)



void *memp_malloc(memp_t type);
#ifndef mem_malloc
#define mem_malloc malloc
#endif


#endif /*_ALINIX_KERNEL_MEMORY_H*/