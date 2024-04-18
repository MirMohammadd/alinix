#ifndef __ALINIX_KERNEL_FONT_H
#define __ALINIX_KERNEL_FONT_H

#include <alinix/types.h>
struct Font
{
    uint8_t* data           ; // Raw font data including header
    char* name              ; // Name of this font, stored inside data buffer
    int size                ; // Size of this font in points
    uint32_t* offsetTable   ; // Offsets for each character data sorted by character

};
void BoundingBox(const char* string, int* retW, int* retH, const void* data, const int* offsetTable)


#endif /*__ALINIX_KERNEL_FONT_H*/