#ifndef _ALINIX_KERNEL_CHESS_PV_H
#define _ALINIX_KERNEL_CHESS_PV_H

#include "board.h"
#include "move.h"
#include "util.h"


namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Defining the Macros
        */
        #define PV_CLEAR(pv) (*(pv)=MoveNone)

        /**
         * @brief Defining functions here
        */
        extern bool pv_is_ok(const mv_t pv[]);

        extern void pv_copy(mv_t dst[],const mv_t src[]);
        extern void pv_cat       (mv_t dst[], const mv_t src[], int move);

        extern bool pv_to_string (const mv_t pv[], char string[], int size);
    }
}

#endif /*_ALINIX_KERNEL_CHESS_PV_H*/