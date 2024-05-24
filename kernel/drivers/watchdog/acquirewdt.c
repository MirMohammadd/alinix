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

/**
 * @abstraction:
 *  - Kernel watchdog implemented here.
*/

#include <alinix/kernel.h>
#include <alinix/types.h>
#include <alinix/err.h>
#include <alinix/platfrom_device.h>
#include <alinix/watchdog.h>
#include <alinix/port.h>
#include <alinix/platform_device.h>
#include <alinix/driver.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel watchdog driver implementation")
MODULE_LICENSE("AGPL")

#define WATCHDOG_MINOR 130

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
/* You must set this - there is no sane way to probe for this board. */
static int wdt_start = 0x443;

static bool nowayout = WATCHDOG_NOWAYOUT;

PRIVATE VOID acq_keepalive(NO_ARGS){
    /* Write a watchdog value*/
    inportb(wdt_start);

}

PRIVATE VOID acq_stop(NO_ARGS){
    inportb(wdt_stop); // Make it stop
}

static ssize_t acq_write( const char  *buf,
						size_t count, loff_t *ppos);


PRIVATE int acq_probe(struct platform_device *dev){
    int ret;

    if (wdt_start != wdt_stop){
        perror("I/O address 0x%04x already in use\n", wdt_stop);
        ret = -5;
        goto out;
    }

    if (ret != 0)
        perror("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);

    out:
        return ret;

}

static void acq_shutdown(struct platform_device *dev)
{
	/* Turn the WDT off if we have a soft shutdown */
	acq_stop();
}

static void acq_remove(struct platform_device *dev)
{
	if (wdt_stop != wdt_start)
		return;
}

static struct platform_driver acquirewdt_driver = {
	.remove_new	= acq_remove,
	.shutdown	= acq_shutdown,
	.driver		= {
		.name	= DRV_NAME,
	},
};