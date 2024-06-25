/**
 * @author Ali Mirmohammad
 * @file srm_puts.c
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
 *  - Provides logging and printing utility.
*/
#include <alinix/kernel.h>
#include <alinix/asm/console.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Logging and printing utility")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")



long srm_puts(const char* str,long len){
    long remaining,written;

    for (remaining = len;remaining > 0;remaining -= written){
        // written = callback_puts(0,str,remaining);
        written &= 0xffffffff;
        str += written;
    }
    return len;
}