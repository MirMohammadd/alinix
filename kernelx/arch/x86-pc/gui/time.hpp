#ifndef _HEISEN_KERNEL_LIB_TIME_H
#define _HEISEN_KERNEL_LIB_TIME_H

#include "types.hpp"

namespace LIBHeisenKernel{
    class Time{
        public:
            static void sleep(uint32_t ms);

            static uint64_t Ticks();
    };
};

#endif // _HEISEN_KERNEL_LIB_TIME_H