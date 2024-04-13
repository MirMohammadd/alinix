#ifndef _ALINIX_KERNEL_APPS_CHESS_GAME_COLOUR__H
#define _ALINIX_KERNEL_APPS_CHESS_GAME_COLOUR__H

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

        /**
         * @brief Defining the functions
        */
        extern void   hash_init         ();

        extern uint64_t hash_key          (const board_t * board);
        extern uint64_t hash_pawn_key     (const board_t * board);
        extern uint64_t hash_material_key (const board_t * board);

        extern uint64_t hash_piece_key    (int piece, int square);
        extern uint64_t hash_castle_key   (int flags);
        extern uint64_t hash_ep_key       (int square);
        extern uint64_t hash_turn_key     (int colour);
}}

#endif /*_ALINIX_KERNEL_APPS_CHESS_GAME_H*/