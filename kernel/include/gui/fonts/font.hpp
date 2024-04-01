#ifndef _HEISEN_KERNEL_FONT_HPP
#define _HEISEN_KERNEL_FONT_HPP

#include <types.hpp>

//LIBHeisenKernel 

namespace LIBHeisenKernel
{
    struct Font
    {
        uint8_t* data           = 0; // Raw font data including header
        char* name              = 0; // Name of this font, stored inside data buffer
        int size                = 0; // Size of this font in points
        uint32_t* offsetTable   = 0; // Offsets for each character data sorted by character

        void BoundingBox(char* str, int* retW, int* retH);
    };
}

#endif // _HEISEN_KERNEL_FONT_HPP