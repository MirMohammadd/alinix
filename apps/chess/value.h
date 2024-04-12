#ifndef ALINIX_KERNEL_CHESS_APPS_HEADER_H
#define ALINIX_KERNEL_CHESS_APPS_HEADER_H

#include <types.h>
#include "piece.h"

using namespace HeisenOs::common;
using namespace LIBHeisenKernel::engine;

namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Defining some constants here for value.h
        */
        const int ValuePawn = 100;
        const int ValueKnight = 325;
        const int ValueBishop = 325;
        const int ValueRook = 500;
        const int ValueQueen = 1000;
        const int ValueKing = 10000;

        const int ValueNone    = -32767;
        const int ValueDraw    = 0;
        const int ValueMate    = 30000;
        const int ValueInf     = ValueMate;
        const int ValueEvalInf = ValueMate - 256; // handle mates upto 255 plies
    }
};

#endif /*ALINIX_KERNEL_CHESS_APPS_HEADER_H*/