/**
 * @author Ali Mirmohammad
 * @file mem.c
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
 *  - Kernel mem for IPV4 driver.
*/

#include <alinix/types.h>
#include <net/mem.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel mem for IPV4 driver")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

struct memp_malloc_helper
{
   memp_t poolnr;
};

/**
 * Free a memory block previously allocated by mem_malloc.
 *
 * @param rmem The memory block to free.
 *
 * @note This function frees a memory block previously allocated by mem_malloc.
 *       It first gets the original struct memp_malloc_helper that was saved when the memory block was allocated.
 *       It then puts the helper back into the pool it was allocated from.
 *
 * @see mem_malloc, memp_free
 */
void
mem_free(void *rmem)
{
  struct memp_malloc_helper *hmem;

  LWIP_ASSERT("rmem != NULL", (rmem != NULL));
  LWIP_ASSERT("rmem == MEM_ALIGN(rmem)", (rmem == LWIP_MEM_ALIGN(rmem)));

  /* get the original struct memp_malloc_helper */
  hmem = (struct memp_malloc_helper*)(void*)((uint8_t*)rmem - LWIP_MEM_ALIGN_SIZE(sizeof(struct memp_malloc_helper)));

  LWIP_ASSERT("hmem != NULL", (hmem != NULL));
  LWIP_ASSERT("hmem == MEM_ALIGN(hmem)", (hmem == LWIP_MEM_ALIGN(hmem)));
  LWIP_ASSERT("hmem->poolnr < MEMP_MAX", (hmem->poolnr < MEMP_MAX));

  /* and put it in the pool we saved earlier */
  memp_free(hmem->poolnr, hmem);
}