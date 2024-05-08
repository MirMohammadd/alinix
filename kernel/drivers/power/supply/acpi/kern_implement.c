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


void uacpi_kernel_log(enum uacpi_log_level lvl, const char* text, ...)
{
    va_list vlist;
    va_start(vlist, text);

    uacpi_kernel_vlog(lvl, text, vlist);

    va_end(vlist);
}

void uacpi_kernel_vlog(enum uacpi_log_level lvl, const char* text, va_list vlist)
{
    const char *lvl_str;

    switch (lvl) {
    case UACPI_LOG_DEBUG:
        lvl_str = "DEBUG";
        break;
    case UACPI_LOG_TRACE:
        lvl_str = "TRACE";
        break;
    case UACPI_LOG_INFO:
        lvl_str = "INFO";
        break;
    case UACPI_LOG_WARN:
        lvl_str = "WARN";
        break;
    case UACPI_LOG_ERROR:
        lvl_str = "ERROR";
        break;
    default:
        ;
    }

}