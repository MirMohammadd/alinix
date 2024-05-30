/**
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