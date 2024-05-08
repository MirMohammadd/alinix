#ifndef __ALINIX_KERNEL__UCAPI_CONTEXT_H
#define __ALINIX_KERNEL__UCAPI_CONTEXT_H

#include <alinix/types.h>
#include "acpi.h"
#include "uacpi.h"
extern struct uacpi_runtime_context g_uacpi_rt_ctx;


struct uacpi_runtime_context {
    /*
     * A local copy of FADT that has been verified & converted to most optimal
     * format for faster access to the registers.
     */
    struct acpi_fadt fadt;

    /*
     * A cached pointer to FACS so that we don't have to look it up in interrupt
     * contexts as we can't take mutexes.
     */
    struct acpi_facs *facs;

    /*
     * pm1{a,b}_evt_blk split into two registers for convenience
     */
    struct acpi_gas pm1a_status_blk;
    struct acpi_gas pm1b_status_blk;
    struct acpi_gas pm1a_enable_blk;
    struct acpi_gas pm1b_enable_blk;

#define UACPI_SLEEP_TYP_INVALID 0xFF
    u8 last_sleep_typ_a;
    u8 last_sleep_typ_b;

    u8 s0_sleep_typ_a;
    u8 s0_sleep_typ_b;

    /*
     * This is a per-table value but we mimic the NT implementation:
     * treat all other definition blocks as if they were the same revision
     * as DSDT.
     */
    bool is_rev1;

#if UACPI_REDUCED_HARDWARE == 0
    bool is_hardware_reduced;
    bool has_global_lock;
    uacpi_handle sci_handle;
#endif

#define UACPI_INIT_LEVEL_EARLY 0
#define UACPI_INIT_LEVEL_TABLES_LOADED 1
#define UACPI_INIT_LEVEL_NAMESPACE_LOADED 2
#define UACPI_INIT_LEVEL_NAMESPACE_INITIALIZED 3
    u8 init_level;

    struct uacpi_params params;
};


#endif