/**
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

#ifndef _CPU_CONTEXT_H_
#define _CPU_CONTEXT_H_

#include <lib/types.h>
#include <lib/status.h>

struct cpu_state;

/*
 * The type of the functions passed as arguments to the Kernel thread
 * related functions.
 */
typedef void (cpu_kstate_function_arg1_t(uint32_t arg1));

void cpu_kstate_init(struct cpu_state **kctxt,
		cpu_kstate_function_arg1_t *start_func,
		uint32_t start_arg,
		uint32_t stack_base,
		uint32_t stack_size);

void cpu_context_switch(struct cpu_state **from_ctxt,
		struct cpu_state *to_ctxt);

#endif // _CPU_CONTEXT_H_
