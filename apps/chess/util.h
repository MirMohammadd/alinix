#ifndef ALINIX_KERNEL_APPS_CHESS_H_UTIL_H_HEADER
#define ALINIX_KERNEL_APPS_CHESS_H_UTIL_H_HEADER

namespace LIBHeisenKernel
{
    namespace engine
    {
        struct my_timer_t {
        double start_real;
        double start_cpu;
        double elapsed_real;
        double elapsed_cpu;
        bool running;
        };
    extern void   my_fatal              (const char format[], ...);
    }
}

#endif //ALINIX_KERNEL_APPS_CHESS_H