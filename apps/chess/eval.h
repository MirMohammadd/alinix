#ifndef _ALINIX_KERNEL_APPS_HEADER_H
#define _ALINIX_KERNEL_APPS_HEADER_H

#include "board.h"
#include "util.h"

namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Defining some useful functions
        */
        extern void eval_init();
        extern int  eval      (const board_t * board);
    }
}

#endif /*_ALINIX_KERNEL_APPS_HEADER_H*/