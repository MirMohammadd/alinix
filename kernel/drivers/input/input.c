/**
 * @author Ali Mirmohammad
 * @file input.c
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
 * 	- Provide util over the input I/O.
*/
#include <alinix/input.h>
#include <alinix/ktime.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/arch/amigaw.h>
#include <alinix/iommufd_utils.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Input/Output abstraction")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

#define INPUT_IGNORE_EVENT	0
#define INPUT_PASS_TO_HANDLERS	1
#define INPUT_PASS_TO_DEVICE	2
#define INPUT_SLOT		4
#define INPUT_FLUSH		8
#define INPUT_PASS_TO_ALL	(INPUT_PASS_TO_HANDLERS | INPUT_PASS_TO_DEVICE)
static const struct input_value input_value_sync = { EV_SYN, SYN_REPORT, 1 };


static inline int is_event_supported(unsigned int code,
				     unsigned long *bm, unsigned int max)
{
	return code <= max && test_bit(code, bm);
}

static void input_event_des(struct input_dev *dev, int disposition,
				unsigned int type, unsigned int code, int value)
{
	if ((disposition & INPUT_PASS_TO_DEVICE) && dev->event)
		dev->event(dev, type, code, value);

	if (!dev->vals)
		return;

	if (disposition & INPUT_PASS_TO_HANDLERS) {
		struct input_value *v;

		if (disposition & INPUT_SLOT) {
			v = &dev->vals[dev->num_vals++];
			v->type = EV_ABS;
			v->code = ABS_MT_SLOT;
			v->value = dev->mt->slot;
		}

		v = &dev->vals[dev->num_vals++];
		v->type = type;
		v->code = code;
		v->value = value;
	}

	if (disposition & INPUT_FLUSH) {
		// if (dev->num_vals >= 2)
			// input_pass_values(dev, dev->vals, dev->num_vals);
		dev->num_vals = 0;
		/*
		 * Reset the timestamp on flush so we won't end up
		 * with a stale one. Note we only need to reset the
		 * monolithic one as we use its presence when deciding
		 * whether to generate a synthetic timestamp.
		 */
		dev->timestamp[INPUT_CLK_MONO] = ktime_set(0, 0);
	} else if (dev->num_vals >= dev->max_vals - 2) {
		dev->vals[dev->num_vals++] = input_value_sync;
		// input_pass_values(dev, dev->vals, dev->num_vals);
		dev->num_vals = 0;
	}
}

void input_event(struct input_dev *dev,
		 unsigned int type, unsigned int code, int value)
{
	unsigned long flags;

	if (is_event_supported(type, dev->evbit, EV_MAX)) {

		// spin_lock_irqsave(&dev->event_lock, flags);
		// input_handle_event(dev, type, code, value);
		// spin_unlock_irqrestore(&dev->event_lock, flags);
	}
}