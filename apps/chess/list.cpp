#include "board.h"
#include "list.hpp"
#include "move.h"
#include "util.h"
#include "value.h"
#include <types.h>
#include <assert.h>

using namespace LIBHeisenKernel;
using namespace HeisenOs::common;

namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Defining the list structure here
        */
        static const bool UserStrict = true;


        bool list_is_ok(const list_t * list){
            if (list == NULL) return false;

            if (list->size < 0 || list->size >= ListSize) return false;

            return true;

        }

        void list_remove(list_t* list,int pos){
            int i;
            assert(list_is_ok(list));
            assert(pos>=0&& pos < list->size);
            for (i = pos; i < list->size-1; i++) {
            list->move[i] = list->move[i+1];
            list->value[i] = list->value[i+1];
        }

        list->size--;
        }
    }
};