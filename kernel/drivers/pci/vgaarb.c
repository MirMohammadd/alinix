/**
 * @author Ali Mirmohammad
 * @file vgaarb.c
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
#include <alinix/kobject.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel PCI implementation")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

struct pci_dev *vga_default;

/**
 * @brief Sets the default VGA device.
 *
 * This function sets the default VGA device to the specified device. If the
 * specified device is already the default device, the function returns
 * immediately.
 *
 * @param pdev A pointer to the PCI device to set as the default VGA device.
 *
 * @return This function does not return any value.
 *
 * @note The current implementation does not actually set the default device.
 * The commented out lines are placeholders for future implementation.
 */
void vga_set_default_device(struct pci_dev *pdev)
{
	if (vga_default == pdev)
		return;

	// pci_dev_put(vga_default);
	// vga_default = pci_dev_get(pdev);
}