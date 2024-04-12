#ifndef _HEISEN_KERNEL_MOVE_DO_
#define _HEISEN_KERNEL_MOVE_DO_

#include <types.h>
#include "board.h"

namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Functions are defined here
        */
       typedef union {
        struct undo{
            bool capture;
            
            int capture_square;
            int capture_piece;
            int capture_pos;

            int pawn_pos;

            int turn;
            int flags;
            int ep_square;
            int ply_nb;

            int cap_sq;

            int opening;
            int endgame;

            uint16_t key;
            uint16_t pawn_key;
            uint16_t material_key;
        };

        
       }undo_t;

    extern void move_do_init   ();

    extern void move_do        (board_t * board, int move, undo_t * undo);
    extern void move_undo      (board_t * board, int move, const undo_t * undo);

    extern void move_do_null   (board_t * board, undo_t * undo);
    extern void move_undo_null (board_t * board, const undo_t * undo);

    }
}

#endif /*_HEISEN_KERNEL_MOVE_DO_*/