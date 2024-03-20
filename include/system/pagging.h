#ifndef PAGING_H
#define PAGING_H

#include <multiboot.h>

#include "support_defs.h"

#define PAGING_STACK_ADDR 0xFF000000

#define SUPERVISOR 0

void kernel_init_paging (uint32_t start);

uint32_t kernel_alloc_page ();

void kernel_free_page (uint32_t p);

void kernel_map_memory(struct multiboot_info* info);

#endif