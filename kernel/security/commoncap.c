/**
 * @author Ali Mirmohammad
 * @file commoncap.c
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
 *  - Commoncap for the kernel security.
*/

#include <alinix/kernel.h>
#include <alinix/kern_levels.h>
#include <alinix/security/commoncap.h>
#include <alinix/time.h>
#include <alinix/capability.h>
#include <alinix/types.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Commoncap for the kernel security")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


/**
 * @ref https://github.com/torvalds/linux/blob/master/security/commoncap.c
*/

/**
 * Prints a warning message if a file has both setuid-root and
 * effective capabilities.
 *
 * @param fname The name of the file.
 *
 * @return void
 *
 * @throws None
 */
static void warn_setuid_and_fcaps_mixed(const char *fname){
    static int warned;
    if (!warned){
        print(KERN_INFO "warning: `%s' has both setuid-root and"
			" effective capabilities. Therefore not raising all"
			" capabilities.\n", fname);
        warned = 1;
    }
}


/**
 * cap_settime - Determine whether the current process may set the system clock
 * @ts: The time to set
 * @tz: The timezone to set
 *
 * Determine whether the current process may set the system clock and timezone
 * information, returning 0 if permission granted, -ve if denied.
 */
int cap_settime(const struct timespec64 *ts,const struct timezone *tz){
	if (!capable(CAP_SYS_TIME))
		return -EPERM;
	return 0;
}
