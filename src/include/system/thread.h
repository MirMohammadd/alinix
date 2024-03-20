#ifndef THREAD_H
#define THREAD_H

#include "support_defs.h"

struct thread_list;

typedef struct
{
  uint32_t esp, ebp, ebx, esi, edi, eflags;
  uint32_t id;                  // Thread ID.
  volatile uint32_t exit;
} thread_t;


thread_t* kernel_init_threading();

// If stack is 0 a default one is created
thread_t* kernel_create_thread(int (*fn)(void*), void* arg, uint32_t* stack);

void switch_thread(struct thread_list* next);

#endif