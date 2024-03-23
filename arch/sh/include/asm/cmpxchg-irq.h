#ifndef __ASM_SH_CMPXCHG_IRQ_H
#define __ASM_SH_CMPXCHG_IRQ_H


#include <heisen/irqflags.h>
#include <heisen/typing.h>
#include <uapi/asm-generic/int-ll64.h>

static inline unsigned long xchg_u32(volatile uint32_t *m, unsigned long val)
{
	unsigned long flags, retval;

	local_irq_save(flags);
	retval = *m;
	*m = val;
	local_irq_restore(flags);
	return retval;
}

static inline unsigned long xchg_u16(volatile uint16_t *m, unsigned long val)
{
	unsigned long flags, retval;

	local_irq_save(flags);
	retval = *m;
	*m = val;
	local_irq_restore(flags);
	return retval;
}

static inline unsigned long xchg_u8(volatile uint8_t *m, unsigned long val)
{
	unsigned long flags, retval;

	local_irq_save(flags);
	retval = *m;
	*m = val & 0xff;
	local_irq_restore(flags);
	return retval;
}

static inline unsigned long __cmpxchg_u32(volatile int *m, unsigned long old,
	unsigned long new)
{
	__u32 retval;
	unsigned long flags;

	local_irq_save(flags);
	retval = *m;
	if (retval == old)
		*m = new;
	local_irq_restore(flags);       /* implies memory barrier  */
	return retval;
}

#endif /* __ASM_SH_CMPXCHG_IRQ_H */