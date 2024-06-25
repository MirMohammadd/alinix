/**
 * @author Ali Mirmohammad
 * @file hooks.c
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
 *  - Hooks for the security of the kernel.
*/


#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/lsm_hooks.h>
#include <alinix/init.h>
#include <alinix/module.h>

#define LSM_ID_BPF 109

/**
 * @ref https://github.com/torvalds/linux/blob/master/security/bpf/hooks.c
*/


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("BPF LSM hooks")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

static const struct lsm_id bpf_lsmid  = {
	.name = "bpf",
	.id = LSM_ID_BPF,
};

