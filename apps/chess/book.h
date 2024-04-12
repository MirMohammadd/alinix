#ifndef _HEISEN_KERNEL_BOOK_APPS_HEADER_H
#define _HEISEN_KERNEL_BOOK_APPS_HEADER_H

#include "board.h"

namespace LIBHeisenKernel
{
    namespace engine{
        extern void book_init  ();

        extern void book_open  (const char file_name[]);
        extern void book_close ();

        extern int  book_move  (board_t * board);
    };
};

#endif /*_HEISEN_KERNEL_BOOK_APPS_HEADER_H*/