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
 *  - Kernel graphics driver.
*/
#include <alinix/paging.h>
#include <alinix/mm.h>
#include <alinix/kernel.h>
#include <alinix/mouse.h>

mouse_info_t *get_mouse_info();



void paint_desktop() {
    draw_rect(0, 0, 1024, 768, 0xCE2C2C);
    paint_windows();
    paint_mouse();
}

void paint_mouse() {
    return;
    // draw_rect(get_mouse_info()->x, get_mouse_info()->y, 10, 10, 0xFFFFFF);
}