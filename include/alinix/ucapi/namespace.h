#ifndef __ALINIX_KERNEL_UAPI_NAME_SPACE_H
#define __ALINIX_KERNEL_UAPI_NAME_SPACE_H

#include <alinix/ucapi/types.h>
#include "types.h"

struct uacpi_field_unit;
typedef struct uacpi_object {
    struct uacpi_shareable shareable;
    u8 type;
    u8 flags;

    union {
        u64 integer;
        uacpi_package *package;
        uacpi_buffer_field buffer_field;
        uacpi_object *inner_object;
        uacpi_control_method *method;
        uacpi_buffer *buffer;
        uacpi_mutex *mutex;
        uacpi_event *event;
        uacpi_buffer_index buffer_index;
        uacpi_operation_region *op_region;
        uacpi_device *device;
        uacpi_processor *processor;
        uacpi_thermal_zone *thermal_zone;
        uacpi_address_space_handlers *address_space_handlers;
        uacpi_handlers *handlers;
        uacpi_power_resource power_resource;
        uacpi_field_unit *field_unit;
    };
} uacpi_object;



typedef enum uacpi_predefined_namespace {
    UACPI_PREDEFINED_NAMESPACE_ROOT = 0,
    UACPI_PREDEFINED_NAMESPACE_GPE,
    UACPI_PREDEFINED_NAMESPACE_PR,
    UACPI_PREDEFINED_NAMESPACE_SB,
    UACPI_PREDEFINED_NAMESPACE_SI,
    UACPI_PREDEFINED_NAMESPACE_TZ,
    UACPI_PREDEFINED_NAMESPACE_GL,
    UACPI_PREDEFINED_NAMESPACE_OS,
    UACPI_PREDEFINED_NAMESPACE_OSI,
    UACPI_PREDEFINED_NAMESPACE_REV,
    UACPI_PREDEFINED_NAMESPACE_MAX = UACPI_PREDEFINED_NAMESPACE_REV,
} uacpi_predefined_namespace;
uacpi_namespace_node *uacpi_namespace_get_predefined(
    uacpi_predefined_namespace
);

uacpi_namespace_node *uacpi_namespace_root(void);

#endif