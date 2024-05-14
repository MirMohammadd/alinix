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
#ifndef __ALINIX_KERNEL_RT_81_39_H  
#define __ALINIX_KERNEL_RT_81_39_H

#include <alinix/types.h>


#define TO_SUM_IO_ADDRESS 0x52
#define OUT_PORT_RTL_ADDRESS 0x0

struct pci_config_space{
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t command;
    uint16_t status;
    uint8_t revision_id;
    uint8_t prog_if;
    uint8_t subclass;
    uint8_t class_code;
    uint8_t cache_line_size;
    uint8_t latency_timer;
    uint8_t header_type;
    uint8_t bist;
    uint32_t bar[6]; // Base Address Registers
    uint32_t cardbus_cis;
    uint16_t subsys_vendor_id;
    uint16_t subsys_id;
    uint32_t expansion_rom_base;
    uint8_t capabilities_ptr;
    uint8_t reserved[7];
    uint8_t interrupt_line;
    uint8_t interrupt_pin;
    uint8_t min_grant;
    uint8_t max_latency;
    uint8_t ioaddr;
};

// MAC Control Registers
struct mac_control_regs {
    uint32_t tx_status[4]; // Transmit status of the four Tx buffers
    uint32_t tx_addr[4];   // Addresses of the four Tx buffers
    uint32_t rx_buf;       // Receive buffer address
    uint32_t rx_early_cnt; // Early Rx byte count
    uint32_t rx_early_status; // Early Rx status
    uint16_t command;
    uint16_t intr_mask;    // Interrupt mask
    uint16_t intr_status;  // Interrupt status
    uint32_t tx_config;    // Transmit configuration
    uint32_t rx_config;    // Receive configuration
    uint32_t timer;        // Timer
    uint32_t rx_missed;    // Missed packet count
    uint32_t rx_overflow;  // Rx overflow
    uint32_t tx_underflow; // Tx underflow
    uint8_t mac_addr[6];   // MAC address
    uint8_t reserved[2];
};

// EEPROM Control Registers
struct eeprom_control_regs {
    uint32_t eeprom_cmd;   // EEPROM command
    uint32_t eeprom_data;  // EEPROM data
};

// DMA Control Registers
struct dma_control_regs {
    uint32_t dma_addr;     // DMA address
    uint32_t dma_len;      // DMA length
    uint32_t dma_cmd;      // DMA command
    uint32_t dma_status;   // DMA status
};

// RTL8139 Network Interface Controller
struct rtl8139 {
    struct pci_config_space pci_config;   // PCI configuration space
    struct mac_control_regs mac_ctrl;     // MAC control registers
    struct eeprom_control_regs eeprom_ctrl; // EEPROM control registers
    struct dma_control_regs dma_ctrl;     // DMA control registers
};

void rtl8139_init(struct rtl8139 *dev); // Used to initiate the rtl8139

void rtl8139_interrupt(struct rtl8139 *dev);

void rtl8139_eoi(struct rtl8139 *dev);

void rtl8139_set_irq(int irq);

void rtl8139_clear_irq(int irq);

void rtl8139_handle_irq(int irq);

#endif

