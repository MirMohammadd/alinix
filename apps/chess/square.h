#ifndef _HEISEN_SQUARE_LIB_APPS_CHESS_GAMES_H
#define _HEISEN_SQUARE_LIB_APPS_CHESS_GAMES_H

#include "colour.h"

namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Constants are defined here
        */

        const int FileNb = 16;
        const int RandNb = 16;

        const int squareNb = FileNb*RandNb;

        const unsigned int FileInc = 1;
    };
};

#endif // _HEISEN_SQUARE_LIB_APPS_CHESS_GAMES_H