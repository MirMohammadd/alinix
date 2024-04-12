#ifndef _ALINIX_KERNEL_CHESS_APPS_VECTOR_H
#define _ALINIX_KERNEL_CHESS_APPS_VECTOR_H

#include "piece.h"
#include "square.h"
#include "util.h"
#include "vector.h"
#include <assert.h>


namespace LIBHeisenKernel
{
    namespace engine
    {
        /**
         * @brief Defining the variables 
        */
        int distance[DeltaNb];

        /**
         * @brief Functions are defined here
        */
        void vector_init(){
            int delta;
            int x,y;
            int dist,tmp;

            for (delta = 0; delta < DeltaNb;delta++)Distance[delta] = -1;

            for (y = -7;y <= 7;y++){
                for (x = -7;x <=7;x++){
                    delta = y*16+x;
                    assert(delta_is_ok(delta));

                    dist = 0;

                    tmp = x;
                    if (tmp < 0) tmp = -tmp;
                    if (tmp > dist) dist = tmp;
                    
                    tmp = y;
                    if (tmp < 0) tmp = -tmp;
                    if (tmp > dist) dist = tmp;

                    Distance[DeltaOffset+delta] = dist;

                }
            }

        }

        bool data_is_ok(int delta){
            if (delta < -119 || delta > 119) return false;
            if ((delta & 0xF) == 8) return false; // HACK: delta % 16 would be ill-defined for negative numbers

            return true;
        }
    };
};

#endif /*_ALINIX_KERNEL_CHESS_APPS_VECTOR_H*/