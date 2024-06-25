/**
 * @author Ali Mirmohammad
 * @file dd.c
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
 * 	- Kernel DD header  for drivers.
*/
#include <alinix/types.h>
#include <alinix/device.h>
#include <alinix/klist.h>
#include <alinix/drivers/base/base.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel DD header for drivers")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")


/**
 * Check if a device is bound to a driver.
 *
 * This function checks if a device is bound to a driver. It does this by checking if the device's parent pointer
 * is not NULL and if the klist node for the device's driver is attached to the parent's klist.
 *
 * @param dev The device to check if it is bound.
 *
 * @return true if the device is bound to a driver, false otherwise.
 */
bool device_is_bound(struct device *dev)
{
	return dev->p && klist_node_attached(&dev->p->knode_driver);
}