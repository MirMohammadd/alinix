#ifndef _HEISEN_KERNEL_HPP
#define _HEISEN_KERNEL_HPP


#include "types.hpp"

namespace LIBHeisenKernel{
    template<typename T>
    class Vector{
        private:
            uint32_t size = 0;
            uint32_t capacity = 0;
            T* buffer = 0;

            void reserve(int capacity){
                T* newBuf = new T[capacity];
                 
            }
    };
};

#endif // _HEISEN_KERNEL_HPP