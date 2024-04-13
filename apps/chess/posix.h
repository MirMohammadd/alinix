#ifndef ALINIX_POSIX_CHESS_HEADER_H
#define ALINIX_POSIX_CHESS_HEADER_H

#include "util.h"


namespace LIBHeisenKernel{

    namespace engine{
        /**
         * @brief Defining the functions
        */
        extern bool input_available();

        extern bool now_real();
        extern bool now_cpu();
    }
};

#endif /*ALINIX_POSIX_CHESS_HEADER_H*/