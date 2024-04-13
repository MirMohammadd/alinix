#include <cstring>

#include <assert.h>

#include "board.h"
#include "move.h"
#include "move_do.h"
#include "pv.h"
#include "util.h"

using namespace LIBHeisenKernel;
using namespace LIBHeisenKernel::engine;

namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Defining the variables here
        */
        bool pv_is_ok(const mv_t pv[]) {

        int pos;
        int move;

        if (pv == NULL) return false;

        for (pos = 0; true; pos++) {

            if (pos >= 256) return false;
            move = pv[pos];

            if (move == MoveNone) return true;
            if (!move_is_ok(move)) return false;
        }

        return true;
        }

        void pv_copy(mv_t dst[], const mv_t src[]) {

            assert(pv_is_ok(src));
            assert(dst!=NULL);

            while ((*dst++ = *src++) != MoveNone)
                ;
            }
        
        void pv_cat(mv_t dst[],const mv_t src[],int move){
            assert(pv_is_ok(src));
            assert(dst!=NULL);

            *dst++ = move;
            while ((*dst++ = *src++) != MoveNone)
                ;
        }

        bool pv_to_string(const mv_t pv[], char string[], int size) {

            int pos;
            int move;

            assert(pv_is_ok(pv));
            assert(string!=NULL);
            assert(size>=512);

            // init

            if (size < 512) return false;

            pos = 0;

            // loop

            while ((move = *pv++) != MoveNone) {

                if (pos != 0) string[pos++] = ' ';

                move_to_string(move,&string[pos],size-pos);
                pos += strlen(&string[pos]);
            }

            string[pos] = '\0';

            return true;
            }

    }
}
