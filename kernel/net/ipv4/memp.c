/**
 * @author Ali Mirmohammad
 * @file memp.c
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
 *  - Kernel memp IPV4 implementations.
*/
#include <alinix/types.h>
#include <alinix/compiler.h>
#include <net/opt.h>
#include <net/stats.h>
#include <net/memp.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel memp IPV4 implementations")
MODULE_LICENSE("AGPL-3.0-or-later")
MODULE_VERSION("0.1")

#define MEMP_SIZE           0


struct memp {
  struct memp *next;
#if MEMP_OVERFLOW_CHECK
  const char *file;
  int line;
#endif /* MEMP_OVERFLOW_CHECK */
};

static struct memp *memp_tab[MEMP_MAX];


void
memp_free(memp_t type, void *mem)
{
  struct memp *memp;

  if (mem == NULL) {
    return;
  }
  LWIP_ASSERT("memp_free: mem properly aligned",
                ((mem_ptr_t)mem % MEM_ALIGNMENT) == 0);

  memp = (struct memp *)(void *)((uint8_t*)mem - MEMP_SIZE);

#if MEMP_OVERFLOW_CHECK
#if MEMP_OVERFLOW_CHECK >= 2
  memp_overflow_check_all();
#else
  memp_overflow_check_element_overflow(memp, type);
  memp_overflow_check_element_underflow(memp, type);
#endif /* MEMP_OVERFLOW_CHECK >= 2 */
#endif /* MEMP_OVERFLOW_CHECK */

//   MEMP_STATS_DEC(used, type); 
  
  memp->next = memp_tab[type]; 
  memp_tab[type] = memp;

#if MEMP_SANITY_CHECK
  LWIP_ASSERT("memp sanity", memp_sanity());
#endif /* MEMP_SANITY_CHECK */

}

const uint16_t memp_sizes[MEMP_MAX] = {
#define LWIP_MEMPOOL(name,num,size,desc)  LWIP_MEM_ALIGN_SIZE(size),
};