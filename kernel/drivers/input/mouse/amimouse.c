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

    struct input_dev *dev = data; // Convert the data?
    unsigned short joy0dat, potgor;
	int nx, ny, dx, dy;

    nx = joy0dat & 0xff;
    nx = joy0dat >> 8;


    dx = nx - amimouse_lastx;
    dy  = ny - amimouse_lasty;

    if (dy < -127) dx = (256+nx)- amimouse_lastx;   /* up */ 
    if (dy > 127) dx = (nx-256) - amimouse_lastx;   /* down */
    if (dy < -127) dy = (256 + ny) - amimouse_lasty;
	if (dy >  127) dy = (ny - 256) - amimouse_lasty;

    amimouse_lastx = nx;
	amimouse_lasty = ny;

    // input_report_key(dev,BTN_LEFT,)
    input_report_rel(dev,REL_X,dx);
    input_report_rel(dev,REL_Y,dy);


}