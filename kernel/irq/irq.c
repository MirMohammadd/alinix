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

/**
 * @abstraction:
 *  - IRQ implemented here.
*/


#include <alinix/irqdesc.h>
#include <alinix/types.h>

#define NR_IRQS 32
struct irq_desc irq_desc_array[NR_IRQS];


struct irq_desc *irq_to_desc(unsigned int irq){
    for (int i = 0;i < irq;i++){
        irq_desc_array->parent_irq = i;
        irq_desc_array->last_unhandled = NULL;
    }
}