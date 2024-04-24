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
#include <net/opt.h>
#include <net/pbuf.h>

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


#ifndef LWIP_MEM_ALIGN_SIZE
#define LWIP_MEM_ALIGN_SIZE(size) (((size) + MEM_ALIGNMENT - 1) & ~(MEM_ALIGNMENT-1))
#endif


const uint16_t memp_sizes[MEMP_MAX] = {
#define LWIP_MEMPOOL(name,num,size,desc)  LWIP_MEM_ALIGN_SIZE(size),
};


#define memp_malloc(type)     mem_malloc(memp_sizes[type])

typedef uint16_t mem_size_t;


#endif /*_ALINIX_KERNEL_MEMORY_H*/