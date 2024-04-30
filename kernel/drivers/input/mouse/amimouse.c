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
 * @ref https://github.com/torvalds/linux/blob/master/drivers/input/mouse/amimouse.c
*/

#include <alinix/kernel.h>
#include <alinix/string.h>
#include <alinix/irqreturn.h>
#include <alinix/input.h>

PRIVATE int amimouse_lastx, amimouse_lasty;

PRIVATE irqreturn_t amimouse_interrupt(int irq,void *data){
    /**
     * @brief Function that defines  how to handle mouse interrupts.
     *        It reads data from mouse device and calculate the movement distance.
    */


}