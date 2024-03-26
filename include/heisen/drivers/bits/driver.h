#ifndef DRIVER_H
#define  DRIVER_H

#include <heisen/typing.h>

struct driver_desc {
    int type;
    uint32_t flags;
    uint32_t listened_device_mask;
    uint32_t listened_driver_mask;
};


#endif // DRIVER_H