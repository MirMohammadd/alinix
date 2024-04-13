#ifndef _HEISEN_KERNEL_APPS_HEADER_H_PAWN_HEADER_H
#define _HEISEN_KERNEL_APPS_HEADER_H_PAWN_HEADER_H

#include "board.h"
#include "colour.h"
#include <types.h>

using namespace LIBHeisenKernel;

namespace LIBHeisenKernel{
    /**
     * @brief Defining some useful macros
    */
    #define BIT(n)       (BitEQ[n])

    #define BIT_FIRST(b) (BitFirst[b])
    #define BIT_LAST(b)  (BitLast[b])
    #define BIT_COUNT(b) (BitCount[b])
    namespace engine{
        struct pawn_info_t{
            uint32_t lock;
            sint16_t opening;
            sint16_t endgame;
            uint8_t flags[ColorNb];
            uint8_t passes_bits[ColorNb];
            uint8_t single_file[ColorNb];
            uint16_t pad;
        };
    };
};

#endif /*_HEISEN_KERNEL_APPS_HEADER_H_*/