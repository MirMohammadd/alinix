#ifndef _ALINIX_KERNEL_APPS_HEADER_CHESS_GAME
#define _ALINIX_KERNEL_APPS_HEADER_CHESS_GAME

#include "board.h"
#include "util.h"

namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Functions are defined here
        */
        extern int see_move   (int move, const board_t * board);
        extern int see_square (const board_t * board, int to, int colour);
    }
}

#endif /*_ALINIX_KERNEL_APPS_HEADER_CHESS_GAME*/