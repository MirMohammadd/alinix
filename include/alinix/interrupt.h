#ifndef __ALINIX_KERNEL_INTERRUPT_H
#define __ALINIX_KERNEL_INTERRUPT_H





enum irqchip_irq_state {
	IRQCHIP_STATE_PENDING,		/* Is interrupt pending? */
	IRQCHIP_STATE_ACTIVE,		/* Is interrupt in progress? */
	IRQCHIP_STATE_MASKED,		/* Is interrupt masked? */
	IRQCHIP_STATE_LINE_LEVEL,	/* Is IRQ line high? */
};
typedef enum irqreturn irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

struct irqaction {
	irq_handler_t		handler;
	void			*dev_id;
	void 	*percpu_dev_id;
	struct irqaction	*next;
	irq_handler_t		thread_fn;
	// struct task_struct	*thread;
	struct irqaction	*secondary;
	unsigned int		irq;
	unsigned int		flags;
	unsigned long		thread_flags;
	unsigned long		thread_mask;
	const char		*name;
	// struct proc_dir_entry	*dir;
} ;



#endif // __ALINIX_KERNEL_INTERRUPT_H