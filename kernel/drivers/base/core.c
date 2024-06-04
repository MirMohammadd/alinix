/**
 * @author Ali Mirmohammad
 * @file core.c
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
 * 	- Provide util for kernel core section.
*/
#include <alinix/kernel.h>
#include <alinix/pci.h>
#include <alinix/kobject.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel core section")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")



static LIST_HEAD(deferred_sync);
static unsigned int defer_sync_state_count = 1;
static DEFINE_MUTEX(fwnode_link_lock);
static bool fw_devlink_is_permissive(void);
static void __fw_devlink_link_to_consumers(struct device *dev);
static bool fw_devlink_drv_reg_done;
static bool fw_devlink_best_effort;


/**
 * Release a reference to a device.
 *
 * This function releases a reference to a device. It decrements the reference count of the device's kobject.
 * If the reference count reaches 0, the kobject is destroyed and the device is freed.
 *
 * @param dev The device to release the reference for.
 *
 * @return void
 */
void put_device(struct device *dev)
{
	/* might_sleep(); */
	if (dev)
		// kobject_put(&dev->kobj);
        return; // TODO: Fix here
}