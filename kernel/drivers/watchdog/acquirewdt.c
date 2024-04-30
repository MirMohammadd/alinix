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
#include <alinix/types.h>
#include <alinix/err.h>
#include <alinix/platfrom_device.h>



/* Module information */
#define DRV_NAME "acquirewdt"
#define WATCHDOG_NAME "Acquire WDT"
/* There is no way to see what the correct time-out period is */
#define WATCHDOG_HEARTBEAT 0

/* internal variables */
/* the watchdog platform device */
static struct platform_device *acq_platform_device;
static unsigned long acq_is_open;
static char expect_close;

/* module parameters */
/* You must set this - there is no sane way to probe for this board. */
static int wdt_stop = 0x43;
