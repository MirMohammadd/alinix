#ifndef _ALINIX_KERNEL_APPS_CHESS_GAME_HEADER_H
#define _ALINIX_KERNEL_APPS_CHESS_GAME_HEADER_H


#include <csetjmp>

#include "board.h"
#include "list.hpp"
#include "move.h"
#include "util.h"

using namespace LIBHeisenKernel::Chess::engine;
using namespace HeisenOs::common;

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

        struct search_info_t{
            jmp_buf buf;
            bool can_stop;
            bool stop;
            int check_nb;
            int check_inc;
            double last_time;
        };
        struct search_root_t {
        list_t list[1];
        int depth;
        int move;
        int move_pos;
        int move_nb;
        int last_value;
        bool bad_1;
        bool bad_2;
        bool change;
        bool easy;
        bool flag;
        };

        struct search_best_t {
        int move;
        int value;
        int flags;
        int depth;
        mv_t pv[HeightMax];
        };

        struct search_current_t {
        board_t board[1];
        my_timer_t timer[1];
        int max_depth;
        sint64_t node_nb;
        double time;
        double speed;
        double cpu;
        };
    };
};

#endif /*_ALINIX_KERNEL_APPS_CHESS_GAME_HEADER_H*/