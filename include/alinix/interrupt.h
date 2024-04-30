#ifndef __ALINIX_KERNEL_INTERRUPT_H
#define __ALINIX_KERNEL_INTERRUPT_H

enum irqchip_irq_state {
	IRQCHIP_STATE_PENDING,		/* Is interrupt pending? */
	IRQCHIP_STATE_ACTIVE,		/* Is interrupt in progress? */
	IRQCHIP_STATE_MASKED,		/* Is interrupt masked? */
	IRQCHIP_STATE_LINE_LEVEL,	/* Is IRQ line high? */
};

#endif // __ALINIX_KERNEL_INTERRUPT_H