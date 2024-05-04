#ifndef __ALINIX_KERNEL_PROGRESS_H
#define __ALINIX_KERNEL_PROGRESS_H

#include <alinix/types.h>
#include <alinix/gui/directgui.h>

typedef struct {
    int x;
    int y;
    int w;
    int h;

    uint32_t background;
    uint32_t foreground;
    uint32_t borderColor;
} ProgressBar;

void ProgressBarInit(ProgressBar *pb, int x_p, int y_p, int width, int height) {
    pb->x = x_p;
    pb->y = y_p;
    pb->w = width;
    pb->h = height;
    pb->background = 0xFFFFFFFF;
    pb->foreground = 0xFF00FF00;
    pb->borderColor = 0xFF000000;
}

#endif // 