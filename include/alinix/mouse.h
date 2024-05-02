#ifndef __ALINIX_KERNEL_MOUSE_H
#define __ALINIX_KERNEL_MOUSE_H

#include <alinix/types.h>


#define MOUSE_PORT 0x60
#define MOUSE_STATUS  0x80
#define MOUSE_ABIT 0x02
#define MOUSE_BBIT 0x01
#define MOUSE_WRITE  0xD4
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08


/*Mouse clocks defined here*/


#define LEFT_CLICK      0x1
#define RIGHT_CLICK     0x2
#define MIDDLE_CLICK    0x4

typedef struct mouse_info{
    int x;
    int y;
    uint32_t buttons;  
}mouse_info_t;

void mouse_handler();
void mouse_init();
void mouse_check_bounds() ;
uint8_t mouse_read() ;
void mouse_write(uint8_t write) ;
void mouse_wait(uint8_t type) ;
mouse_info_t *get_mouse_info();
#endif // __ALINIX_KERNEL_MOUSE_H