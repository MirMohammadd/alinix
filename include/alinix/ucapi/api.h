#ifndef __ALINIX_KERNEL_UCAPI_API__INCLUDED_H
#define __ALINIX_KERNEL_UCAPI_API__INCLUDED_H

enum uacpi_log_level {
    /*
     * Super verbose logging, every op & uop being processed is logged.
     * Mostly useful for tracking down hangs/lockups.
     */
    UACPI_LOG_DEBUG = 4,

    /*
     * A little verbose, every operation region access is traced with a bit of
     * extra information on top.
     */
    UACPI_LOG_TRACE = 3,

    /*
     * Only logs the bare minimum information about state changes and/or
     * initialization progress.
     */
    UACPI_LOG_INFO  = 2,

    /*
     * Logs recoverable errors and/or non-important aborts.
     */
    UACPI_LOG_WARN  = 1,

    /*
     * Logs only critical errors that might affect the ability to initialize or
     * prevent stable runtime.
     */
    UACPI_LOG_ERROR = 0,
};


uacpi_status uacpi_kernel_raw_io_read(
    u64 address, u8 byte_width, u64 *out_value
);
uacpi_status uacpi_kernel_raw_io_write(
    u64 address, u8 byte_width, u64 in_value
);


#endif