#ifndef _HEISEN_KERNEL_BOARD_H
#define _HEISEN_KERNEL_BOARD_H

#include "colour.h"
#include "piece.h"
#include "square.h"
#include <types.h>

using namespace LIBHeisenKernel::Chess::engine;
using namespace LIBHeisenKernel::engine;
using namespace HeisenOs::common;


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

    /**
     * @brief Useful types defined here
    */

    struct board_t{
        int square[squareNb];
        int pos[squareNb];

        sq_t piece[ColorNb][32];
        int piece_size[ColorNb];

        sq_t pawn[ColourNb][16]; // Just define 9
        int pawn_size[ColourNb];
        
        int piece_nb;
        int number[16]; // only 12 are needed

        int pawn_file[ColourNb][FileNb];

        int turn;
        int flags;
        int ep_square;
        int ply_nb;
        int sp; // TODO: MOVE ME?

        int cap_sq;

        int opening;
        int endgame;

        uint64_t key;
        uint64_t pawn_key;
        uint64_t material_key;

        uint64_t stack[StackSize];
    };

    /**
     * @brief Useful functions
    */

    extern bool board_is_ok         (const board_t * board);

    extern void board_clear         (board_t * board);
    extern void board_copy          (board_t * dst, const board_t * src);

    extern void board_init_list     (board_t * board);

    extern bool board_is_legal      (const board_t * board);
    extern bool board_is_check      (const board_t * board);
    extern bool board_is_mate       (const board_t * board);
    extern bool board_is_stalemate  (board_t * board);

    extern bool board_is_repetition (const board_t * board);

    extern int  board_material      (const board_t * board);
    extern int  board_opening       (const board_t * board);
    extern int  board_endgame       (const board_t * board);
};


#endif // _HEISEN_KERNEL_BOARD_H