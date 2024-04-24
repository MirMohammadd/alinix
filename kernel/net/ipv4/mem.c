#include <alinix/types.h>
#include <net/mem.h>

struct memp_malloc_helper
{
   memp_t poolnr;
};


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