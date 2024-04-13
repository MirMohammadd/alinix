#ifndef ALINIX_KERNEL_CHESS_FEN_H
#define ALINIX_KERNEL_CHESS_FEN_H

#include "board.h"
#include "util.h"

namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Defining the constants
        */
        extern const char* const StartFen;
        /**
         * @brief Defining some functions
        */
        extern void board_from_fen(board_t* board,const char fen[]);
        extern bool board_to_fen   (const board_t * board, char fen[], int size);
        
    }
}

#endif /*ALINIX_KERNEL_CHESS_FEN_H*/