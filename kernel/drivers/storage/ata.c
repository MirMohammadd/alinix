/**
 * @author Ali Mirmohammad
 * @file ata.c
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
 *  - Implements ATA storage driver.
*/

#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/port.h>
#include <alinix/atapi.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("ATA storage driver")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")


static void ata_io_wait(const uint8_t p){
	inportb(p + CONTROL + ALTERNATE_STATUS);
	inportb(p + CONTROL + ALTERNATE_STATUS);
	inportb(p + CONTROL + ALTERNATE_STATUS);
	inportb(p + CONTROL + ALTERNATE_STATUS);
}

/**
 * @brief reads the cdorm from I/O
 * @note Always checks the LSB  to state the clear bit.
*/

int read_cdrom(uint16_t port, bool slave, uint32_t lba, uint32_t sectors, uint16_t *buffer){
            // The command
	volatile uint8_t read_cmd[12] = {0xA8, 0,
	                                 (lba >> 0x18) & 0xFF, (lba >> 0x10) & 0xFF, (lba >> 0x08) & 0xFF,
	                                 (lba >> 0x00) & 0xFF,
	                                 (sectors >> 0x18) & 0xFF, (sectors >> 0x10) & 0xFF, (sectors >> 0x08) & 0xFF,
	                                 (sectors >> 0x00) & 0xFF,
	                                 0, 0};
                
        outportb(port + DRIVE_SELECT,0xA0 & (slave << 4));
        ata_io_wait(port);
        outportb(port + ERROR_R,0x00);
        outportb(port + LBA_MID, 2048 & 0xFF);
        outportb(port + LBA_HIGH, 2048 >> 8);
        outportb(port + COMMAND_REGISTER, 0xA0); // Packet command
        ata_io_wait(port); // I think we might need this delay, not sure, so keep this

        // Halt here for status
        while (1){
            uint8_t status = inportb(port + COMMAND_REGISTER);
            if ((status & 0x01) == 0){
                return 1;
            }
            if (!(status & 0x80) && (status & 0x08))
                break;
		ata_io_wait(port);
        }
        outsw(port + DATA, (uint16_t *) read_cmd, 6);

        for (uint32_t i = 1; i < sectors;i++){
            		while (1) {
			uint8_t status = inportb(port + COMMAND_REGISTER);
			if (status & 0x01)
				return 1;
			if (!(status & 0x80) && (status & 0x08))
				break;
		}
 
		int size = inportb(port + LBA_HIGH) << 8
		           | inportb(port + LBA_MID); // Get the size of transfer
 
		insw(port + DATA, (uint16_t *) ((uint8_t *) buffer + i * 0x800), size / 2); // Read it
        }


}