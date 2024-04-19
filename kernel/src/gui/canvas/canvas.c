#include <alinix/gui/canvas.h>
#include <alinix/types.h>

void Canvas_SetPixel(int x, int y, uint32_t color){
*(uint32_t*)((uint32_t)bufferPointer + (y * Width * 4 + x * 4)) = color;
}


uint32_t Canvas_GetPixel(int x, int y){
    return *(uint32_t*)((uint32_t)bufferPointer + (y * Width * 4 + x * 4));

}