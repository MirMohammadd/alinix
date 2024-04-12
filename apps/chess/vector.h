#ifndef _HEISEN_KERNEL_VECTOR_APPS_CHESS_GAME_H
#define _HEISEN_KERNEL_VECTOR_APPS_CHESS_GAME_H

#include <types.h>

namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Functions are defined here
        */
        const int IncNone = 0;
        const int IncNb = 2 * 17 + 1;
        const int IncOffset = 17;

        const int DeltaNone = 0;
        const int DeltaNb = 2 * 119 + 1;
        const int DeltaOffset = 119;
        /**
         * @brief Macros are defined here
        */
        #define DISTANCE(square_1,square_2) (Distance[DeltaOffset+((square_2)-(square_1))])


        extern int Distance[DeltaNb];

        extern void vector_init ();

        extern bool delta_is_ok (int delta);
        extern bool inc_is_ok   (int inc);
    }
}

#endif /*_HEISEN_KERNEL_VECTOR_APPS_CHESS_GAME_H*/