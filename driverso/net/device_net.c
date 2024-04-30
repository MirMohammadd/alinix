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

#include <net/device_net.h>
#include <asm/fcntl.h>

struct ixy_device* ixy_init(const char* pci_addr, uint16_t rx_queues, uint16_t tx_queues, int interrupt_timeout) {
	// Read PCI configuration space
	// For VFIO, we could access the config space another way
	// (VFIO_PCI_CONFIG_REGION_INDEX). This is not needed, though, because
	// every config file should be world-readable, and here we
	// only read the vendor and device id.
	int config = pci_open_resource(pci_addr, "config", O_RDONLY);
	uint16_t vendor_id = read_io16(config, 0);
	uint16_t device_id = read_io16(config, 2);
	uint32_t class_id = read_io32(config, 8) >> 24;
	close(config);
	if (class_id != 2) {
		error("Device %s is not a NIC", pci_addr);
	}
	if (vendor_id == 0x1af4 && device_id >= 0x1000) {
		return virtio_init(pci_addr, rx_queues, tx_queues);
	} else {
		// Our best guess is to try ixgbe
		return ixgbe_init(pci_addr, rx_queues, tx_queues, interrupt_timeout);
	}
}