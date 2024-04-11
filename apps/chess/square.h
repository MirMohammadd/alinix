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

        const unsigned int RankInc = 16;

        const int FileNone = 0;

        const int FileA = 0x4;
        const int FileB = 0x5;
        const int FileC = 0x06;
        const int FileD = 0x07;
        const int FileE = 0x08;
        const int FileF = 0x09;
        const int FileG = 0x0A;
        const int FileH = 0x0B;

        const int RankNone = 0;

        const int Rank1 = 0x4;
        
        const int Rank2 = 0x5;
        const int Rank3 = 0x6;
        const int Rank4 = 0x7;
        const int Rank5 = 0x8;
        const int Rank6 = 0x9;
        const int Rank7 = 0xA;
        const int Rank8 = 0xB;

    };
};

#endif // _HEISEN_SQUARE_LIB_APPS_CHESS_GAMES_H