#ifndef __ALINIX_KERNEL_SETTINGS_H
#define __ALINIX_KERNEL_SETTINGS_H




static inline bool irq_settings_is_per_cpu_devid(struct irq_desc *desc)
{
	return desc->status_use_accessors & _IRQ_PER_CPU_DEVID;
}



#endif