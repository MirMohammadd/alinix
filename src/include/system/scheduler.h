#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <thread.h>

#include "support_defs.h"

typedef struct thread_list
{
  thread_t *thread;
  struct thread_list *next;
} thread_list_t;

void kernel_init_scheduler(thread_t* initial_thread);

void kernel_activate_thread(thread_t* thread);

void kernel_deactivate_thread(thread_t* thread);

thread_t* kernel_get_current_thread();

void schedule();

#endif