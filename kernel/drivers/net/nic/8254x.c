/**
 * @author Ali Mirmohammad
 * @file 8254.c
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
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/port.h>
#include <alinix/types.h>
#include <alinix/module.h>
#include <alinix/RTL8139.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("8254x Intel net interface")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

#include "8254x.h"

#define I8254X_EECD   0x00000010 /* EEPROM/Flash Control - RW */
#define I8254X_EECD_EE_PRES (1 << 8) /* EEPROM Present */


static uint16_t i8254x_read_eeprom(uint8_t addr,struct pci_config_space *dev){
    uint16_t tmp;
    uint16_t data;
    if((le32_to_cpu(mmio_read_dword(I8254X_EECD,I8254X_EERD)) & I8254X_EECD_EE_PRES) == 0) {
        Log(Info,"EEPROM present bit is not set for i8254x\n");
    }
    if(dev->version == I82547GI_EI
    || dev->version == I82541EI_A0
    || dev->version == I82541EI_B0
    || dev->version == I82541ER_C0
    || dev->version == I82541GI_B1
    || dev->version == I82541PI_C0) {
        tmp = ((uint16_t)addr & 0xfff ) << 2;
    }else{
        tmp = ((uint32_t)addr & 0xff) << 8;
    }

    tmp |= I8254X_EERD_START;

    tmp |= I8254X_EERD_START;
    mmio_write_dword(dev->mmio.addr, I8254X_EERD);
 
    /* Wait until the read is finished - then the DONE bit is cleared */
    timeout((le32_to_cpu(mmio_read_dword(dev->mmio.addr, I8254X_EERD)) & I8254X_EERD_DONE) == 0, 100);
 
    /* Obtain the data */
    data = (uint16_t)(le32_to_cpu(mmio_read_dword(dev->mmio.addr, I8254X_EERD)) >> 16);
 
    /* Tell EEPROM to stop reading */
    tmp = le32_to_cpu(mmio_read_dword(dev->mmio.addr, I8254X_EERD));
    tmp &= ~(uint32_t)I8254X_EERD_START;
    mmio_write_dword(dev->mmio.addr, I8254X_EERD);
    return data;

}
