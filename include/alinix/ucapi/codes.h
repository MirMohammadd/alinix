#ifndef __ALINIX_KERNEL_CODES_H
#define __ALINIX_KERNEL_CODES_H

#include <alinix/types.h>

struct uacpi_op_spec {
    char *name;
    union {
        u8 decode_ops[16];
        u8 *indirect_decode_ops;
    };
    u8 properties;
    uint16_t code;
};

#endif