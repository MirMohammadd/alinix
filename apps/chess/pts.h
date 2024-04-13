#ifndef ALINIX_KERNEL_PTS_CHESS_GAME_HEADER_H
#define ALINIX_KERNEL_PTS_CHESS_GAME_HEADER_H

#include "util.h"
#include <types.h>

using namespace LIBHeisenKernel;
using namespace HeisenOs::common;


namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Defining the constants
        */
        const int Opening = 0;
        const int Endgame = 1;
        const int StageNb = 2;

        /**
         * @brief Defining the macros
        */
        #define PST(piece_12,square_64,stage) (Pst[piece_12][square_64][stage])

        /**
         * @brief variables
        */
        extern sint16_t Pst[12][64][StageNb]; // piece-to-square tables for opening and endgames
        extern void pst_init();
    }
}

#endif /*ALINIX_KERNEL_PTS_CHESS_GAME_HEADER_H*/