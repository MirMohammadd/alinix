/**
 * @author Ali Mirmohammad
 * @file ulib.c
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
 *  - lib of the main kernel.
*/


#include <alinix/types.h>
#include <alinix/syscall.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel Module")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")


uint syscall(uint service, void *param)
{
  uint __res = 0;
  __asm__ volatile( "int $49;"
                  : "=a" ((uint)(__res))
                  : "0" (service), "b" ((uint)(service)),"c" ((void*)(param))
                  : "memory"
                );
  return __res;
}
void *malloc(size_t size)
{
  return (void*)syscall(SYSCALL_MEM_ALLOCATE, &size);
}