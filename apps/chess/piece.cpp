#include "colour.h"
#include "piece.h"

namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Constants defined here 
        */
        const int PawnMake[ColourNb] = { WhitePawn256, BlackPawn256 };
        const int PieceFrom12[12] = {
            WhitePawn256,   BlackPawn256,
            WhiteKnight256, BlackKnight256,
            WhiteBishop256, BlackBishop256,
            WhiteRook256,   BlackRook256,
            WhiteQueen256,  BlackQueen256,
            WhiteKing256,   BlackKing256,
        };
    };
};