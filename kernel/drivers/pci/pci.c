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
 * @file pci.c
 * @date 18 may 2024
*/

#include <alinix/init.h>
#include <alinix/module.h>
#include <alinix/kernel.h>
#include <alinix/pci.h>
#include <alinix/types.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("PCI Driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

/**
 * Reads a 16-bit value from the PCI configuration space.
 * 
 * @param bus Bus number of the PCI device.
 * @param slot Slot number of the PCI device.
 * @param func Function number of the PCI device.
 * @param offset Offset within the configuration space to read from.
 * @return The 16-bit value read from the specified configuration space offset.
 */
uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset){
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;

    // Create configuration address as per Figure 1
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
    
    outportl(0xCF8,address);

    tmp = (uint16_t)((inportl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
    return tmp;
}

/**
 * @brief Check the Vendor ID of a PCI device at a specified bus and slot.
 * 
 * @param bus The bus number of the PCI device.
 * @param slot The slot number of the PCI device.
 * @return uint16_t The Vendor ID of the PCI device.
 */
uint16_t pciCheckVendor(uint8_t bus, uint8_t slot) {
    uint16_t vendor,device;
    if ((vendor == pciConfigReadWord(bus,slot,0,0)) != 0xFFFF){
        device = pciConfigReadWord(bus, slot, 0, 2);
    }
    return (vendor);
}

void checkDevice(uint8_t bus, uint8_t device){
    uint16_t vendor;
    vendor = pciCheckVendor(bus,device);
    if (vendor == 0x8086){
        RET;
    }
}


void checkFunction(uint8_t bus, uint8_t device, uint8_t function) {
}

/**
 * @brief Function to check the Vendor ID of a PCI device and take action based on the result
 */

/**
 * @brief Check the Vendor ID of a PCI device and take action based on the result.
 * 
 * This function checks the Vendor ID of a PCI device located at a specific bus and device number. If the Vendor ID matches a specific value (0x8086 in this case), a certain action is taken.
 * 
 * @param bus The bus number of the PCI device.
 * @param device The device number of the PCI device.
 */
void checkAllBuses(void){
    uint16_t bus;
    uint16_t device;
    for (bus = 0;bus < 256;bus++){
        for (device = 0; device < 32;device++){
            checkDevice(bus,device);
        }
    }
}

/**
 * @brief Function to check devices on a specific bus
 */

/**
 * @brief Check devices on a specific bus.
 * 
 * This function iterates through the devices (0-31) on a specific bus and calls the checkDevice function to check the Vendor ID.
 * 
 * @param bus The bus number to check devices on.
 */
void checkBus(uint8_t bus){
    uint8_t device;
    for (device = 0;device < 32;device++){
        checkDevice(bus,device);
    }
}

/**
 * @brief Function to calculate the MSI address for a given MSI request
 */

/**
 * @brief Calculate the MSI address for a given MSI request.
 * 
 * This function calculates the MSI address based on the provided parameters.
 * 
 * @param data Pointer to store the MSI data.
 * @param vector Vector number for the MSI request (0-255).
 * @param processor Processor ID to target the MSI request.
 * @param edgetrigger Specifies if the MSI is edge-triggered (1) or level-triggered (0).
 * @param deassert Specifies if the MSI deassert message is required (1) or not required (0).
 * @return The MSI address calculated based on the parameters.
 */

uint64_t arch_msi_address(uint64_t *data, size_t vector, uint32_t processor, uint8_t edgetrigger, uint8_t deassert) {
	*data = (vector & 0xFF) | (edgetrigger == 1 ? 0 : (1 << 15)) | (deassert == 1 ? 0 : (1 << 14));
	return (0xFEE00000 | (processor << 12));
}