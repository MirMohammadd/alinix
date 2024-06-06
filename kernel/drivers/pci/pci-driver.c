/**
 * @author Ali Mirmohammad
 * @file pci-driver.c
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
 * 	- Kernel PCI implementation.
*/

#include <alinix/kernel.h>
#include <alinix/pci.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel PCI implementation")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

/**
 * @brief Releases a reference to a PCI device.
 *
 * This function releases a reference to a PCI device previously obtained by
 * calling `pci_dev_get()`. When the last reference is released, the device is
 * freed.
 *
 * @param dev A pointer to the PCI device to release.
 *
 * @return This function does not return anything.
 *
 * @note This function is not yet implemented. The current implementation does
 * nothing and returns immediately.
 */
void pci_dev_put(struct pci_dev *dev)
{
	if (dev)
        return; /* FIXME: Implement this */
		// put_device(&dev->dev);
}