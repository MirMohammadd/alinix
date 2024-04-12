#ifndef ALINIX_KERNEL_APPS_CHESS_H
#define ALINIX_KERNEL_APPS_CHESS_H

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
    }
}

#endif //ALINIX_KERNEL_APPS_CHESS_H