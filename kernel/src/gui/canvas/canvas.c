#include <alinix/gui/canvas.h>
#include <alinix/types.h>
#include <alinix/math.h>
#include <alinix/memory.h>

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

void FillCircleHelper(int x, int y, int radius, uint32_t corner, int delta, uint32_t color)
{
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int i = 0;
    int j = radius;
 
    while (i < j) {
        if (f >= 0) {
            j--;
            ddF_y += 2;
            f += ddF_y;
        }
        i++;
        ddF_x += 2;
        f += ddF_x;
 
        if (corner & 0x1) {
            DrawVerticalLine(color, 2 * j + 1 + delta, x + i, y - j);
            DrawVerticalLine(color, 2 * i + 1 + delta, x + j, y - i);
        }
        if (corner & 0x2) {
            DrawVerticalLine(color, 2 * j + 1 + delta, x - i, y - j);
            DrawVerticalLine(color, 2 * i + 1 + delta, x - j, y - i);
        }
    }
}

void DrawCircleHelper(int x, int y, int radius, uint32_t corner, uint32_t color)
{
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int i = 0;
    int j = radius;
 
    while (i < j) {
        if (f >= 0) {
            j--;
            ddF_y += 2;
            f += ddF_y;
        }
        i++;
        ddF_x += 2;
        f += ddF_x;
        if (corner & 0x4) {
            SetPixel(x + i, y + j, color);
            SetPixel(x + j, y + i, color);
        }
        if (corner & 0x2) {
            SetPixel(x + i, y - j, color);
            SetPixel(x + j, y - i, color);
        }
        if (corner & 0x8) {
            SetPixel(x - j, y + i, color);
            SetPixel(x - i, y + j, color);
        }
        if (corner & 0x1) {
            SetPixel(x - j, y - i, color);
            SetPixel(x - i, y - j, color);
        }
    }
}

// void Clear()
// {
//     memset((void*)bufferPointer, 0, Width*Height*4);
// }

void DrawFillRoundedRect(uint32_t color, int x, int y, int width, int height, int radius)
{
    // Draw the body
    DrawFillRect(color, x + radius, y, width - 2 * radius + 1, height);
 
    // Draw the four corners
    FillCircleHelper(x + width - radius - 1, y + radius, radius, 1, height - 2 * radius - 1, color);
    FillCircleHelper(x + radius, y + radius, radius, 2, height - 2 * radius - 1, color);
}

void DrawFillRect(uint32_t color, int x_start, int y_start, int width, int height)
{
    for (int y = y_start; y < y_start + height; y++)
    {
        DrawLine(color, x_start, y, x_start + width, y);
    }
}