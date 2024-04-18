#ifndef __LIBCACTUSOS__GUI__FONTS__FONT_H
#define __LIBCACTUSOS__GUI__FONTS__FONT_H

#include <types.h>

namespace LIBHeisenKernel
{
    struct Font
    {
        uint8_t* data           ; // Raw font data including header
        char* name              ; // Name of this font, stored inside data buffer
        int size                ; // Size of this font in points
        uint32_t* offsetTable   ; // Offsets for each character data sorted by character

        void BoundingBox(char* str, int* retW, int* retH);
    };
}

#endif