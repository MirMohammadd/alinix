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
#include <alinix/RTL8139.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/port.h>

/**
 * @ref https://wiki.osdev.org/RTL8139
*/

struct rtl8139 *rtldev;
static inline void rtl8139_init(struct rtl8139 *dev){
    outportb(dev->pci_config.ioaddr + TO_SUM_IO_ADDRESS,OUT_PORT_RTL_ADDRESS); // OUT the data from here 
    do {
        ; // Do nothing here
    }while (inportb(dev->pci_config.ioaddr +SOFTWARE_RESET_IO_PORT) & SOFTWARE_OUT_IO_PORT);
}

static inline VOID set_imr_isr(struct rtl8139 *dev){
    outportw(dev->pci_config.ioaddr + IMR_PORT,IMR_OUT_PORT);
}

/**
 * @note Before hoping to see a packet coming to you, you should tell the RTL8139 to accept packets based on various rules. The configuration register is RCR.
*/

static inline VOID configure_rev_buffer(struct rtl8139 *dev){
    outportl(dev->pci_config.ioaddr + 0x44, 0xf | (1 << 7)); // (1 << 7) is the WRAP bit, 0xf is AB+AM+APM+AAP
}

static inline VOID enable_rec_and_transmit(struct rtl8139 *dev){
    outportb(dev->pci_config.ioaddr + 0x37, 0x0C); // Sets the RE and TE bits high
}

void rtl8139_handler(uint8_t isr, uint64_t error, uint64_t irq,struct rtl8139 *dev) {
    uint16_t status = inportw(dev->pci_config.io_base + 0x3e);
    outportw(dev->pci_config.io_base + 0x3E, 0x05);

    if (status & TOK){
        Log(Info,"RTL Packed has been sent...");
    }
    if (status & ROK){
        Log(Info,"RTL Packed has been received...");
    }
}