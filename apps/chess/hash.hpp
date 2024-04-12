#ifndef _ALINIX_KERNEL_APPS_CHESS_GAME_H
#define _ALINIX_KERNEL_APPS_CHESS_GAME_H

#include "board.h"
#include "util.h"

namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Defining the macros here
        */
        #define KEY_INDEX(key) (uint32(key))
        #define KEY_LOCK(key)  (uint32((key)>>32))

        /**
         * @brief Defining some constants here
        */
        const int RandomPiece     =   0; // 12 * 64
        const int RandomCastle    = 768; // 4
        const int RandomEnPassant = 772; // 8
        const int RandomTurn      = 780; // 1

        /**
         * @brief Defining the variables 
        */
        extern uint16_t Castle[16];
}}

#endif /*_ALINIX_KERNEL_APPS_CHESS_GAME_H*/