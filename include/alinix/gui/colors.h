#ifndef __ALINIX_KERNEL_GUI_COLORS_H
#define __ALINIX_KERNEL_GUI_COLORS_H

#include <alinix/types.h>


typedef union Color4Tag
{
    uint32_t c;
    struct ColorComponents
    {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    } argb;
} Color4;


static const uint32_t Transparent = 0x00000000;

#endif /*__ALINIX_KERNEL_GUI_COLORS_H*/