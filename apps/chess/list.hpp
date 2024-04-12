#ifndef ALINIX_KERNEL_APPS_CHESS_GAME_LIST_HPP
#define ALINIX_KERNEL_APPS_CHESS_GAME_LIST_HPP

#include <types.h>

#ifdef __cplusplus
using namespace HeisenOs::common;
#endif // __cplusplus

#include "board.h"

using namespace LIBHeisenKernel::engine;

namespace LIBHeisenKernel{
    namespace engine{
        
        /**
         * @brief Defining the constants here
        */
        const int ListSize = 256;

        /**
         * @brief Defining the list macro here
        */
        #define LIST_CLEAR(list)     ((list)->size=0)
        #define LIST_ADD(list,mv)    ((list)->move[(list)->size++]=(mv))

        #define LIST_IS_EMPTY(list)  ((list)->size==0)
        #define LIST_SIZE(list)      ((list)->size)

        #define LIST_MOVE(list,pos)  ((list)->move[pos])
        #define LIST_VALUE(list,pos) ((list)->value[pos])

        struct list_t{
            int size;
            uint16_t move[ListSize];
            uint16_t value[ListSize];
        };

        typedef bool (*move_test_t) (int move, board_t * board);

        /**
         * @brief Useful functions are defined here
        */
        extern bool list_is_ok(const list_t * list);
        extern void list_remove(list_t * list,int pos);
        extern void list_copy(list_t * dst,const list_t* src);
        extern void list_sort(list_t* list);
        extern bool list_contain(const list_t* list,int move);
        extern void list_note(list_t* list);
        extern void list_filter   (list_t * list, board_t * board, move_test_t test, bool keep);
    };
};



#endif /*ALINIX_KERNEL_APPS_CHESS_GAME_H*/