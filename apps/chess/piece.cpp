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
        static const char PieceString[12+1] = "PpNnBbRrQqKk";

        const inc_t PawnMoveInc[ColourNb] = {
        +16, -16,
        };

        const inc_t KnightInc[8+1] = {
        -33, -31, -18, -14, +14, +18, +31, +33, 0
        };

        const inc_t BishopInc[4+1] = {
        -17, -15, +15, +17, 0
        };

        const inc_t RookInc[4+1] = {
        -16, -1, +1, +16, 0
        };

        const inc_t QueenInc[8+1] = {
        -17, -16, -15, -1, +1, +15, +16, +17, 0
        };

        const inc_t KingInc[8+1] = {
        -17, -16, -15, -1, +1, +15, +16, +17, 0
        };

        /**
         * @brief Variables defined here
        */
        int PieceTo12[PieceNb];
        int PieceOrder[PieceNb];

        const inc_t * PieceInc[PieceNb];


        void piece_init(){
            int piece,piece12;

            for (piece = 0;piece < PieceNb;piece++)PieceTo12[piece12] = -1;
            for (piece12 = 0; piece12 < 12; piece12++) {
                PieceTo12[PieceFrom12[piece12]] = piece12;
            }
        }

    };
};