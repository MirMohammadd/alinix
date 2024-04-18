#include <alinix/printk.h>

void Print(const char* data, uint32_t length) {
    /* Send data through serial port */
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