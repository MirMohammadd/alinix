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
                    
                    
                }
            }
        }
    };
};

#endif /*_ALINIX_KERNEL_CHESS_APPS_VECTOR_H*/