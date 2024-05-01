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
#include <alinix/video.h>
#include <alinix/gui/window.h>


static int x;
static int y;
struct video_mem vram;
struct vbe_mem vbemem;

void video_init(int h,int w){
    x = 0;
    y = 0;
    vram.height = h;
    vram.width = w;
    vram.ram = (uint16_t *) 0xB8000; // Settle the RAM
}

