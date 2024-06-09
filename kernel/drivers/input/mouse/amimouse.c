/**
 * @author Ali Mirmohammad
 * @file amimouse.c
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
#include <alinix/arch/amigaw.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Amiga Mouse Driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

PRIVATE int amimouse_lastx, amimouse_lasty;

/**
 * @brief Handles mouse interrupts by reading data from the mouse device and calculating movement distance.
 * 
 * This function is called when a mouse interrupt occurs. It reads data from the mouse device,
 * calculates the movement distance in both x and y directions, and reports these movements to the
 * input subsystem. It also handles button presses.
 * 
 * @param irq The interrupt number.
 * @param data Pointer to the input device structure.
 * @return irqreturn_t The result of the interrupt handling, typically IRQ_HANDLED.
 * 
 * @details The function reads the joystick and potentiometer data, calculates the x and y movements, 
 * adjusts for overflows, updates the last known positions, and reports the relative movements and button states.
 * 
 * @note Ensure that the data passed as a parameter is a valid pointer to an input_dev structure. The function 
 * relies on global variables `amimouse_lastx` and `amimouse_lasty` to keep track of the last known x and y positions.
 */
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
    input_report_rel(dev,REL_Y,-dy);

    input_report_key(dev, BTN_LEFT,   ciaa.pra & 0x40);
	input_report_key(dev, BTN_MIDDLE, potgor & 0x0100);
	input_report_key(dev, BTN_RIGHT,  potgor & 0x0400);

    input_sync(dev);

}

/**
 * Initializes the Amiga mouse device.
 *
 * @param dev A pointer to the input device structure.
 *
 * @return Returns 0 on success, or a negative error code on failure.
 *
 * @throws None.
 *
 * @details
 * This function initializes the Amiga mouse device by setting the last x and y
 * coordinates to the current joystick data. It reads the joystick data from
 * the `joy0dat` register of the Amiga custom chip and stores the x-coordinate in
 * the lower 8 bits and the y-coordinate in the upper 8 bits of the `joy0dat`
 * variable. The function then assigns the values of `joy0dat` to the `amimouse_lastx`
 * and `amimouse_lasty` variables.
 *
 * @note
 * This function assumes that the `amiga_custom` structure is defined and contains
 * the `joy0dat` member.
 */
PRIVATE int amimouse_open(struct input_dev *dev){
    unsigned short joy0dat;
	int error;

	joy0dat = amiga_custom.joy0dat;

	amimouse_lastx = joy0dat & 0xff;
	amimouse_lasty = joy0dat >> 8;
}