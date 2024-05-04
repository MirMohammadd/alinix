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

static ProgressBar* progressBar;

void ProgressBarInit(ProgressBar *pb, int x_p, int y_p, int width, int height);

#endif // 