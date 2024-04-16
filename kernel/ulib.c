#include <alinix/types.h>
#include <alinix/syscall.h>
#include <stdlib.h>

// void *malloc(size_t size)
// {
//   return (void*)syscall(SYSCALL_MEM_ALLOCATE, &size);
// }