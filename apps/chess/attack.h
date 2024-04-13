#ifndef _ALINIX_KERNEL_ATTACK_H_CHESS_HEADER
#define _ALINIX_KERNEL_ATTACK_H_CHESS_HEADER

#include "vector.h"
#include "util.h"
#include "board.h"

namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Defining the macros
        */
        #define IS_IN_CHECK(board,colour)         (is_attacked((board),KING_POS((board),(colour)),COLOUR_OPP((colour))))

        #define DELTA_INC_LINE(delta)             (DeltaIncLine[DeltaOffset+(delta)])
        #define DELTA_INC_ALL(delta)              (DeltaIncAll[DeltaOffset+(delta)])
        #define DELTA_MASK(delta)                 (DeltaMask[DeltaOffset+(delta)])

        #define INC_MASK(inc)                     (IncMask[IncOffset+(inc)])

        #define PIECE_ATTACK(board,piece,from,to) (PSEUDO_ATTACK((piece),(to)-(from))&&line_is_empty((board),(from),(to)))
        #define PSEUDO_ATTACK(piece,delta)        (((piece)&DELTA_MASK(delta))!=0)
        #define SLIDER_ATTACK(piece,inc)          (((piece)&INC_MASK(inc))!=0)

        #define ATTACK_IN_CHECK(attack)           ((attack)->dn!=0)

        
    }
}

#endif /*_ALINIX_KERNEL_ATTACK_H_CHESS_HEADER*/