#ifndef __ALINIX_KERNEL_WINDOW_H
#define __ALINIX_KERNEL_WINDOW_H

#include <alinix/types.h>

#define WINDOW_EDGE_COLOR               0xA3A29E
#define WINDOW_BACKGROUND_COLOR         0xE8E6E3
#define TEXT_AREA_COLOR                 0xFFFFF6


#define TYPE_TEXT_AREA                  1

#define TITLE_SIZE 256

typedef struct components{
    uint32_t *component;
    struct components *next;
}components_list_t;


typedef struct window{
    char title[TITLE_SIZE];
    int x;
    int y;
    int h;
    int w;
    components_list_t *components;
}window_t;


#endif // __ALINIX_KERNEL_WINDOW_H