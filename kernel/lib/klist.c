/**
 * @author Ali Mirmohammad
 * @file klist.c
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
 * 	- Provides list for the kernel.
*/
#include <alinix/klist.h>
#include <alinix/kernel.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel List")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")


/**
 * Check if a klist node is attached to a klist.
 *
 * @param n Pointer to the klist node.
 * @return 1 if the klist node is attached to a klist, 0 otherwise.
 *
 * @note This function checks if the given klist node is attached to a klist by checking if its `n_klist` member is not NULL.
 *       If the `n_klist` member is not NULL, it means that the klist node is attached to a klist, and the function returns 1.
 *       If the `n_klist` member is NULL, it means that the klist node is not attached to a klist, and the function returns 0.
 *
 * @example
 * // Check if a klist node is attached to a klist
 * struct klist_node *node = ...;
 * int is_attached = klist_node_attached(node);
 * if (is_attached) {
 *     // The klist node is attached to a klist
 * } else {
 *     // The klist node is not attached to a klist
 * }
 *
 * @see klist_node_attach()
 * @see klist_node_detach()
 */
int klist_node_attached(struct klist_node *n)
{
	return (n->n_klist != NULL);
}