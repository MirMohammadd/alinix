/**
 * @author Ali Mirmohammad
 * @file le32.c
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


#include <alinix/types.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("A simple module to test the module system")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")


uint32_t le32_to_cpu(uint32_t le_value) {
    // Check if the system is little-endian or big-endian
    uint32_t test = 1;
    if (*(uint8_t *)&test == 1) {
        // System is little-endian, no conversion needed
        return le_value;
    } else {
        // System is big-endian, convert from little-endian to big-endian
        return ((le_value & 0x000000FF) << 24) |
               ((le_value & 0x0000FF00) << 8) |
               ((le_value & 0x00FF0000) >> 8) |
               ((le_value & 0xFF000000) >> 24);
    }
}