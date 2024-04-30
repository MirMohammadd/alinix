#include <alinix/kernel.h>
#include <alinix/interrupt.h>
#include <alinix/memory.h>
#include <alinix/settings.h>

const void *free_irq(unsigned int irq, void *dev_id)
{
	struct irq_desc *desc = irq_to_desc(irq);
	struct irqaction *action;
	const char *devname;

	if (!desc || irq_settings_is_per_cpu_devid(desc))
		return NULL;

#ifdef CONFIG_SMP
	if (WARN_ON(desc->affinity_notify))
		desc->affinity_notify = NULL;
#endif

	// action = __free_irq(desc, dev_id);

	if (!action)
		return NULL;

	devname = action->name;
	free(action);
	return devname;
}