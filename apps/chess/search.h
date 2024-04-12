#ifndef _ALINIX_KERNEL_APPS_CHESS_GAME_HEADER_H
#define _ALINIX_KERNEL_APPS_CHESS_GAME_HEADER_H

#include "board.h"
#include "list.hpp"
#include "move.h"
#include "util.h"

namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Define some constants here
        */
        const int DepthMax = 64;
        const int HeightMax = 256;

        const int SearchNormal = 0;
        const int SearchShort  = 1;

        const int SearchUnknown = 0;
        const int SearchUpper   = 1;
        const int SearchLower   = 2;
        const int SearchExact   = 3;

        /**
         * @brief Defining some types
        */
        struct search_input_t{
            board_t board[1];
            list_t list[1];
            bool infinite;
            bool depth_is_limited;
            int depth_limit;
            bool time_is_limited;
            double time_limit_1;
            double time_limit_2;
        };
    };
};

#endif /*_ALINIX_KERNEL_APPS_CHESS_GAME_HEADER_H*/