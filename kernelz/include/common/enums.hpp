#ifndef _HEISEN_KERNEL_Z_ENUMS_HPP
#define _HEISEN_KERNEL_Z_ENUMS_HPP

#ifdef __cplusplus
extern "C"{
#endif
namespace HeisenOs
{
    enum class PowerState
    {
        None,
        Reboot,
        Shutdown
    };
    #if defined(__cplusplus)
    enum class Priority{
        /*A class that defined a proccess priority*/
        LOWEST = -150,
        LOWER = -50,
        LOW = -10,
        NORMAL = 0,
        HIGH = 10,
        HIGHER = 50,
        HIGHEST = 150
    };
    #else 
    typedef enum
    {
        /*A class that defined a proccess priority*/
        LOWEST = -150,
        LOWER = -50,
        LOW = -10,
        NORMAL = 0,
        HIGH = 10,
        HIGHER = 50,
        HIGHEST = 150
    }Priority;
    #endif 
}
#ifdef __cplusplus
}
#endif

#endif /*_HEISEN_KERNEL_Z_ENUMS_HPP*/