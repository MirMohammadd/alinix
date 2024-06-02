/**
 * @author Ali Mirmohammad
 * @file manage.c
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - Manages the IRQ.
*/


#include <alinix/kernel.h>
#include <alinix/interrupt.h>
#include <alinix/memory.h>
#include <alinix/settings.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("IRQ Manager")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

/**
 * free_irq - Frees an interrupt request
 * @irq: The interrupt number to free
 * @dev_id: A pointer to the device ID associated with the interrupt
 *
 * This function releases an interrupt request that was previously allocated
 * to a device. It removes the specified interrupt handler from the system,
 * ensuring that it will no longer handle the specified interrupt.
 *
 * Return: A constant void pointer to the device name associated with the IRQ if
 * successful, or NULL if the IRQ cannot be freed due to various conditions
 * (e.g., invalid descriptor, per-CPU device ID).
 */
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
#endif /*CONFIG_SMP*/

	// action = __free_irq(desc, dev_id);

	if (!action)
		return NULL;

	devname = action->name;
	free(action);
	return devname;
}