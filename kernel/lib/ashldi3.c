/**
 * @author Ali Mirmohammad
 * @file ashldi3.c
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
 * 	- Util of the kernel library package.
*/
#include <alinix/kernel.h>
#include <alinix/libgcc.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel library")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

/**
 * Perform a left shift on a 64-bit signed integer by a specified number of bits.
 *
 * @param u The 64-bit signed integer to be shifted.
 * @param b The number of bits to shift by.
 * @return The result of the left shift operation.
 *
 * @note This function is an implementation of the `__ashldi3` function, which is used to perform a left shift on a 64-bit signed integer.
 *       The function takes two parameters: `u`, which is the 64-bit signed integer to be shifted, and `b`, which is the number of bits to shift by.
 *       The function first checks if the shift amount is zero, in which case it returns the original value of `u`.
 *       If the shift amount is greater than zero, the function performs the left shift operation.
 *       It first calculates the bit mask `bm` by subtracting the shift amount from 32.
 *       If `bm` is less than or equal to zero, it sets the low part of the result to zero and shifts the high part of `u` by the negative of `bm`.
 *       If `bm` is greater than zero, it calculates the carries by shifting the low part of `u` by `bm` and stores them in the high part of the result.
 *       It then shifts the low part of `u` by `b` and stores the result in the low part of the result.
 *
 * @example
 * // Shift the value 0x1234567890ABCDEF left by 4 bits
 * long long result = __ashldi3(0x1234567890ABCDEF, 4);
 * // The result will be 0x9876543210ABCDEF
 *
 * @see https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc/Shift-and-Rotate-Operators.html#Shift-and-Rotate-Operators
 */
long long  __ashldi3(long long u, int b){
    DWunion uu, w;
    int bm;

    if (b == 0)
        return u;
    uu.ll = u;
    bm = 32 - b;
    if (bm <= 0) {
		w.s.low = 0;
		w.s.high = (unsigned int) uu.s.low << -bm;
	} else {
		const unsigned int carries = (unsigned int) uu.s.low >> bm;

		w.s.low = (unsigned int) uu.s.low << b;
		w.s.high = ((unsigned int) uu.s.high << b) | carries;
	}

	return w.ll;
}