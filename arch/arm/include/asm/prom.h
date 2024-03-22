#ifndef __ASMARM_PROM_H
#define __ASMARM_PROM_H

#include <heisen/typing.h>

#ifdef CONFIG_OF   



extern const struct machine_desc *setup_machine_fdt(void *dt_virt);
extern void __init arm_dt_init_cpu_maps(void);

#else
static inline const struct machine_desc *setup_machine_fdt(void *dt_virt)
{
	return NULL;
}

static inline void arm_dt_init_cpu_maps(void) { }


#endif


#endif