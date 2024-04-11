#ifndef _HEISEN_KERNEL_BOARD_H
#define _HEISEN_KERNEL_BOARD_H

#include "colour.h"
#include "piece.h"
#include "square.h"

using namespace LIBHeisenKernel::Chess::engine;
using namespace LIBHeisenKernel::engine;


namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Some useful constants
        */

        const int Empty = 0;
        const int Edge = Knight64; // HACK: uncoloured knight

        const int WP = WhitePawn256;
        const int WN = WhiteKnight256;
        const int WB = WhiteBishop256;
        const int WR = WhiteRook256;
        const int WQ = WhiteQueen256;
        const int WK = WhiteKing256;

        const int BP = BlackPawn256;
        const int BN = BlackKnight256;
        const int BB = BlackBishop256;
        const int BR = BlackRook256;
        const int BQ = BlackQueen256;
        const int BK = BlackKing256;

        const int FlagsNone = 0;
        const int FlagsWhiteKingCastle  = 1 << 0;
        const int FlagsWhiteQueenCastle = 1 << 1;
        const int FlagsBlackKingCastle  = 1 << 2;
        const int FlagsBlackQueenCastle = 1 << 3;

        const int StackSize = 4096;

        /**
         * @brief Some useful macros
        */

        #define KING_POS(board,colour) ((board)->piece[colour][0])
        

    };
};


#endif // _HEISEN_KERNEL_BOARD_H