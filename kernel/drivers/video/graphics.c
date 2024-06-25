/**
 * @author Ali Mirmohammad
 * @file graphics.c
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
 *  - Kernel graphics driver.
*/
#include <alinix/paging.h>
#include <alinix/mm.h>
#include <alinix/kernel.h>
#include <alinix/mouse.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel graphics driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

mouse_info_t *get_mouse_info();


/**
 * Paints the desktop background.
 *
 * This function is responsible for painting the desktop background.
 * It calls the `draw_rect()` function to draw the desktop rectangle,
 * the `paint_windows()` function to paint the windows, and the `paint_mouse()` function to paint the mouse cursor.
 *
 * @return void
 *
 * @throws None
 */
void paint_desktop() {
    draw_rect(0, 0, 1024, 768, 0xCE2C2C);
    paint_windows();
    paint_mouse();
}

/**
 * @brief Do noting here.
 */
void paint_mouse() {
    return;
    // draw_rect(get_mouse_info()->x, get_mouse_info()->y, 10, 10, 0xFFFFFF);
}