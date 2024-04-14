#ifndef _ALINIX_KERNEL_PRINT_K_HEADER_H
#define _ALINIX_KERNEL_PRINT_K_HEADER_H

#include <alinix/types.h>
#include <alinix/system.h>
#include <alinix/serialport.h>

void Print(const char* data, uint32_t length) {
    if(screenMode == TextMode)
    {
        for (uint32_t i = 0; i < length; i++)
            Write(data[i]);
    }
    else if(Initialized && (gdbEnabled == false))
    {
        for (uint32_t i = 0; i < length; i++)
            Write(data[i]);
    }
}

#endif