#ifndef __ALINIX_KERNEL_UAPI_NAME_SPACE_H
#define __ALINIX_KERNEL_UAPI_NAME_SPACE_H

#include "types.h"

typedef struct uacpi_namespace_node {
    struct uacpi_shareable shareable;
    uacpi_object_name name;
    u32 flags;
    uacpi_object *object;
    struct uacpi_namespace_node *parent;
    struct uacpi_namespace_node *child;
    struct uacpi_namespace_node *next;
} uacpi_namespace_node;

#endif