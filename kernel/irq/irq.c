/**
 * @author Ali Mirmohammad
 * @file irq.c
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
 *  - IRQ implemented here.
*/


#include <alinix/irqdesc.h>
#include <alinix/types.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("IRQ implementation")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")


#define NR_IRQS 32
struct irq_desc irq_desc_array[NR_IRQS];


/**
 * Retrieves the interrupt descriptor for the specified interrupt.
 *
 * @param irq The interrupt number.
 *
 * @return A pointer to the interrupt descriptor.
 *
 * @throws None
 */
struct irq_desc *irq_to_desc(unsigned int irq){
    for (int i = 0;i < irq;i++){
        irq_desc_array->parent_irq = i;
        irq_desc_array->last_unhandled = NULL;
    }
}