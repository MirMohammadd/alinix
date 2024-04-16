#include <alinix/types.h>
#include <alinix/syscall.h>


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