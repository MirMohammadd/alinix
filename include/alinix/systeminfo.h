#ifndef __ALINIX_KERNEL_SYSTEM_INFO_H_
#define __ALINIX_KERNEL_SYSTEM_INFO_H_


struct SharedSystemInfo
{
    unsigned int MouseX;
    unsigned int MouseY;
    signed int   MouseZ;

    bool MouseLeftButton;
    bool MouseRightButton;
    bool MouseMiddleButton;
} __attribute__((packed));

#endif // __ALINIX_KERNEL_SYSTEM_INFO_H_