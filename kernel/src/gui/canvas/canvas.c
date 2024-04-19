#include <alinix/gui/canvas.h>
#include <alinix/types.h>
#include <alinix/math.h>

void Canvas_SetPixel(int x, int y, uint32_t color){
*(uint32_t*)((uint32_t)bufferPointer + (y * Width * 4 + x * 4)) = color;
}


uint32_t Canvas_GetPixel(int x, int y){
    return *(uint32_t*)((uint32_t)bufferPointer + (y * Width * 4 + x * 4));

}

void DrawDiagonalLine(uint32_t color, int dx, int dy, int x1, int y1){
    int i, sdx, sdy, dxabs, dyabs, x, y, px, py;

    dxabs = Abs(dx);
    dyabs = Abs(dy);
    sdx = Sign(dx);
    sdy = Sign(dy);
    x = dyabs >> 1;
    y = dxabs >> 1;
    px = x1;
    py = y1;

    if (dxabs >= dyabs) // the line is more horizontal than vertical
    {
        for (i = 0; i < dxabs; i++)
        {
            y += dyabs;
            if (y >= dxabs)
            {
                y -= dxabs;
                py += sdy;
            }
            px += sdx;
            SetPixel(px, py, color);
        }
    }
    else // the line is more vertical than horizontal
    {
        for (i = 0; i < dyabs; i++)
        {
            x += dxabs;
            if (x >= dyabs)
            {
                x -= dyabs;
                px += sdx;
            }
            py += sdy;
            SetPixel(px, py, color);
        }
    }
}

void DrawVerticalLine(uint32_t color, int dy, int x1, int y1)
{
    for(int i = 0; i < dy; i++)
        SetPixel(x1, y1 + i, color);
}

void DrawLine(uint32_t color, int x1, int y1, int x2, int y2)
{
    int dx, dy;

    dx = x2 - x1;      /* the horizontal distance of the line */
    dy = y2 - y1;      /* the vertical distance of the line */

    if (dy == 0) /* The line is horizontal */
    {
        if(dx < 0)
            DrawHorizontalLine(color, Abs(dx), x2, y1);
        else
            DrawHorizontalLine(color, dx, x1, y1);

        return;
    }

    if (dx == 0) /* the line is vertical */
    {
        if(dy < 0)
            DrawVerticalLine(color, Abs(dy), x1, y2);
        else
            DrawVerticalLine(color, dy, x1, y1);
        
        return;
    }

    /* the line is neither horizontal neither vertical, is diagonal then! */
    DrawDiagonalLine(color, dx, dy, x1, y1);
}

void DrawHorizontalLine(uint32_t color, int dx, int x1, int y1)
{
    for (int i = 0; i < dx; i++)
        SetPixel(x1 + i, y1, color);
}