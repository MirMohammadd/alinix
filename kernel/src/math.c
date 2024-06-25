/**
 * @author Ali Mirmohammad
 * @file math.c
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
#include <alinix/math.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Math module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")


/**
 * Returns the absolute value of a given long integer.
 *
 * @param v The long integer to calculate the absolute value of.
 *
 * @return The absolute value of the given long integer.
 *
 * @throws None
 */
long Abs(long v){
    if(v == 0)
        return 0;
    if(v < 0)
        return -v;
    if(v > 0)
        return v;
    return v;
}

/**
 * Returns the sign of a given long integer.
 *
 * @param v The long integer to determine the sign of.
 *
 * @return -1 if the long integer is negative, 0 if it is zero, and 1 if it is positive.
 *
 * @throws None
 */
long Sign(long v)
{
    if(v < 0)
        return -1;
    if(v == 0)
        return 0;
    if(v > 1)
        return 1;
    return 0;
}