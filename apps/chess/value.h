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
        /**
         * @brief Defining some macros here
        */
        #define VALUE_MATE(height) (-ValueMate+(height))
        #define VALUE_PIECE(piece) (ValuePiece[piece])

        /**
         * @brief variables
        */
        extern int ValuePiece[PieceNb];

        /**
         * @brief functions goes here
        */
        extern void value_init       ();

        extern bool value_is_ok      (int value);
        extern bool range_is_ok      (int min, int max);

        extern bool value_is_mate    (int value);

        extern int  value_to_trans   (int value, int height);
        extern int  value_from_trans (int value, int height);

        extern int  value_to_mate    (int value);
    }
};

#endif /*ALINIX_KERNEL_CHESS_APPS_HEADER_H*/