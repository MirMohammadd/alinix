#ifndef __ALINIX_KERNEL_COMPONENTS_GRAPHIC_DEVICE_HPP
#define __ALINIX_KERNEL_COMPONENTS_GRAPHIC_DEVICE_HPP

#include <alinix/types.h>

class GraphicsDevice
{
public:
    uint32_t width;
    uint32_t height;
    uint8_t bpp;
    uint32_t framebufferPhys;
    char* identifier = 0;

    GraphicsDevice(char* name);
    virtual ~GraphicsDevice();
    virtual bool SelectBestVideoMode();
    
    uint32_t GetBufferSize();
    
    static GraphicsDevice* GetBestDevice();
};
#endif /**/