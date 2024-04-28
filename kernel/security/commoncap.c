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
#include <alinix/kern_levels.h>

static void warn_setuid_and_fcaps_mixed(const char *fname){
    static int warned;
    if (!warned){
        print(KERN_INFO "warning: `%s' has both setuid-root and"
			" effective capabilities. Therefore not raising all"
			" capabilities.\n", fname);
        warned = 1;
    }
}

