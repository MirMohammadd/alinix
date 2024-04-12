#ifndef _HEISEN_KERNEL_OPTIONS_APPS_CHESS_HPP_OPTIONS_HEADER
#define _HEISEN_KERNEL_OPTIONS_APPS_CHESS_HPP_OPTIONS_HEADER

#include <types.h>

namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Functions are defined here
        */

        extern void option_init();
        extern void option_list();
        extern bool option_set(const char var[],const char val[]);
        extern const char* option_get(const char var[]);

        extern bool option_get_bool(const char var[]);
        extern int          option_get_int    (const char var[]);
        extern const char * option_get_string (const char var[]);
    };
};

#endif /*_HEISEN_KERNEL_OPTIONS_APPS_CHESS_H*/