/**
 * @author Ali Mirmohammad
 * @file port.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Provide util for the 8253x Intel net interface.
*/

#include <alinix/port.h>

#include <alinix/RTL8139.h>

#define I82547GI_EI       0x1075  // Actual value for Intel 82547GI
#define I82541EI_A0       0x1010  // Actual value for Intel 82541EI A0
#define I82541EI_B0       0x1011  // Actual value for Intel 82541EI B0
#define I82541ER_C0       0x1015  // Actual value for Intel 82541ER C0
#define I82541GI_B1       0x1076  // Actual value for Intel 82541GI B1
#define I82541PI_C0       0x107C  // Actual value for Intel 82541PI C0

#define I82547GI_EI_VENDOR_ID           0x8086  // Vendor ID for Intel
#define I82547GI_EI_DEVICE_ID           0x1234  // Device ID
#define I82547GI_EI_SUBSYSTEM_VENDOR_ID 0x8086  // Subsystem Vendor ID
#define I82547GI_EI_SUBSYSTEM_ID        0x5678  // Subsystem ID


#define I8254X_EERD_START  0x0001  // Start bit for EEPROM read operation
struct pci_config_space *device;

