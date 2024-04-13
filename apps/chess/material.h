#ifndef _ALINIX_KERNEL_CHESS_GAME_HEADER_MATERIAL_H
#define _ALINIX_KERNEL_CHESS_GAME_HEADER_MATERIAL_H

#include <types.h>

#include "board.h"
#include "list.hpp"
#include "move.h"
#include "util.h"
#include <convert.h>

using namespace HeisenOs::common;

using namespace LIBHeisenKernel;

namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Defining the constants
        */
        enum mat_dummy_t{
            MAT_NONE,
            MAT_KK,
            MAT_KBK, MAT_KKB,
            MAT_KNK, MAT_KKN,
            MAT_KPK, MAT_KKP,
            MAT_KQKQ, MAT_KQKP, MAT_KPKQ,
            MAT_KRKR, MAT_KRKP, MAT_KPKR,
            MAT_KBKB, MAT_KBKP, MAT_KPKB, MAT_KBPK, MAT_KKBP,
            MAT_KNKN, MAT_KNKP, MAT_KPKN, MAT_KNPK, MAT_KKNP,
            MAT_KRPKR, MAT_KRKRP,
            MAT_KBPKB, MAT_KBKBP,
            MAT_NB
        };
        
        const int DrawNodeFlag = 1 << 0;
        const int DrawBishopFlag  = 1 << 1;

        const int MatRookPawnFlag = 1 << 0;
        const int MatBishopFlag   = 1 << 1;
        const int MatKnightFlag   = 1 << 2;
        const int MatKingFlag     = 1 << 3;

        struct material_info_t{
            uint32_t lock;
            uint8_t recog;
            uint8_t flags;
            uint8_t cflags[ColorNb];
            uint8_t mul[ColorNb];
            sint16_t opening;
            sint16_t phase;
            sint16_t endgame;
        };
    }
}

#endif /*_ALINIX_KERNEL_CHESS_GAME_HEADER_MATERIAL_H*/