#ifndef _HEISEN_KERNEL_MOVE_LEGAL_H
#define _HEISEN_KERNEL_MOVE_LEGAL_H

#include "board.h"

namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Functions are defined here
        */
       extern bool move_is_pseudo(int move,board_t * board);
       extern bool quiet_is_pseudo(int move,board_t * board);
       extern bool  pseudo_is_legal(int move,board_t * board);
    }
}

#endif /*_HEISEN_KERNEL_MOVE_LEGAL_H*/