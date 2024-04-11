#ifndef _HEISEN_KERNEL_PROTOCOL_APPS_CHESS_HEADER_H
#define _HEISEN_KERNEL_PROTOCOL_APPS_CHESS_HEADER_H

#include <types.h>

namespace LIBHeisenKernek{
    namespace engine{
        /** @brief Functions are defined here*/
        extern void loop  ();
        extern void event ();

        extern void get   (char string[], int size);
        extern void send  (const char format[], ...);
    };
};

#endif /*_HEISEN_KERNEL_PROTOCOL_APPS_CHESS_HEADER_H*/