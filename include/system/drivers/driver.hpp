#ifndef __ALINIX_KERNEL_SYSTEM_DRIVERS_HPP
#define __ALINIX_KERNEL_SYSTEM_DRIVERS_HPP

#ifndef __cplusplus
#include <alinix/types.h>
#endif /* !__cplusplus */

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

typedef struct Driver Driver;


static char* GetDriverName();
static char* GetDriverDescription();

static bool Initialize();

#ifdef __cplusplus
}
#endif

#endif //__ALINIX_KERNEL_SYSTEM_DRIVERS_HPP