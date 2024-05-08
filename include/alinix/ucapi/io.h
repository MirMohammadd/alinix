#ifndef __ALINIX_KERNEL_U_CAPI_IO_H
#define __ALINIX_KERNEL_U_CAPI_IO_H

#include <alinix/ucapi/acpi.h>
#include <alinix/ucapi/types.h>
#include <alinix/types.h>

uacpi_status uacpi_gas_read(const struct acpi_gas *gas, u64 *value);
uacpi_status uacpi_gas_write(const struct acpi_gas *gas, u64 value);

#endif