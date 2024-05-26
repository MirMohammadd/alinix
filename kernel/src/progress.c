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
 *  - Progress report of kernel.
*/


#include <alinix/progress.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Progress report of kernel.")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")


void ProgressBarInit(ProgressBar *pb, int x_p, int y_p, int width, int height) {
    pb->x = x_p;
    pb->y = y_p;
    pb->w = width;
    pb->h = height;
    pb->background = 0xFFFFFFFF;
    pb->foreground = 0xFF00FF00;
    pb->borderColor = 0xFF000000;
}
