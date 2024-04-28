/**
 * @author Ali Mirmohammad
 * @file kernel.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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

#ifndef _ALINIX_KERNEL_KERNEL_H__
#define _ALINIX_KERNEL_KERNEL_H__

#include <alinix/enums.h>
#include <alinix/syscall.h>
#include <alinix/types.h>
#include <alinix/init.h>
#include <alinix/power_supply.h>
#include <alinix/device.h>

#define ENOMEM 12

typedef struct{
	char character;
	uint8_t color;
} __attribute__((__packed__)) vga_entry_t;

struct kparam_string {
	unsigned int maxlen;
	char *string;
};


struct kernel_param {
	const char *name;
	struct module *mod;
	const struct kernel_param_ops *ops;
	const uint16_t perm;
	sint8_t level;
	uint8_t flags;
	union {
		void *arg;
		const struct kparam_string *str;
		const struct kparam_array *arr;
	};
};

struct kernel_param_ops {
	/* How the ops should behave */
	unsigned int flags;
	/* Returns 0, or -errno.  arg is in kp->arg. */
	int (*set)(const char *val, const struct kernel_param *kp);
	/* Returns length written or -errno.  Buffer is 4k (ie. be short!) */
	int (*get)(char *buffer, const struct kernel_param *kp);
	/* Optional function to free kp->arg when module unloaded. */
	void (*free)(void *arg);
};


vga_entry_t terminal_make_vga_entry(char c);
void terminal_writeline(char* string);
void terminal_scroll();
void terminal_reset_scroll();
void terminal_set_cursor_position(uint8_t x, uint8_t y);

#endif /*_ALINIX_KERNEL_KERNEL_H__*/