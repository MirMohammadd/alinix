#include <alinix/ucapi/api.h>
#include <alinix/ucapi/types.h>



uacpi_status uacpi_kernel_raw_io_write(
    u64, u8, u64
){
    return UACPI_STATUS_OK;
}

uacpi_status uacpi_kernel_raw_io_read(
    u64, u8, u64 *ret
){
    *ret = 0xFFFFFFFFFFFFFFFF;
    return UACPI_STATUS_OK;
}