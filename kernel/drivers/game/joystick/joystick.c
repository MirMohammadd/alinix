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
#include <alinix/gameport.h>
#include <alinix/types.h>
#include <alinix/port.h>
#include <alinix/log.h>
#include <alinix/kernel.h>
#include <alinix/init.h>

bool joystick_button(uint8_t buttonnum){
    int i;
    for (i = 4; i <= 8; ++i){
        if (joystick_values[i] == buttonnum){
            return ((inportb(JOYSTICK_PORT) & buttonnum) == 0);
        }
    }
    srm_printk("Invalid value: %x; Out of bounds.\n", buttonnum);
    return 0;
}

