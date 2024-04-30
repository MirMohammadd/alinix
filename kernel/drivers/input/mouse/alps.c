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

#include <alinix/kernel.h>

/*
 * Definitions for ALPS version 3 and 4 command mode protocol
 */
#define ALPS_CMD_NIBBLE_10	0x01f2

#define ALPS_REG_BASE_RUSHMORE	0xc2c0
#define ALPS_REG_BASE_V7	0xc2c0
#define ALPS_REG_BASE_PINNACLE	0x0000