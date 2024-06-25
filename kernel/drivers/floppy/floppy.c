/**
 * @author Ali Mirmohammad
 * @file floppy.c
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
 *  - Floppy drivers implemented for kernel.
*/
#include <alinix/floppy.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Floppy driver")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")



/**
 * @brief Resets the floppy disk controller and waits for the IRQ.
 * 
 * This function sends a reset signal to the floppy disk controller and then waits for
 * an interrupt request (IRQ) to ensure that the reset has been successfully completed.
 * 
 * @details The function relies on an external `WaitForIRQ` function to handle the waiting 
 * for the IRQ. The specifics of the reset process, such as sending the reset signal, 
 * are assumed to be handled elsewhere in the code.
 * 
 * @note Ensure that the `WaitForIRQ` function is correctly implemented to properly wait 
 * for the IRQ, as this function depends on it for synchronization.
 */
void ResetFloppy()
{
 
    WaitForIRQ();
}

/**
 * Converts a logical block address (LBA) to cylinder-head-sector (CHS) format.
 *
 * @param lba The logical block address to convert.
 * @param cyl A pointer to an uint16_t variable to store the calculated cylinder value.
 * @param head A pointer to an uint16_t variable to store the calculated head value.
 * @param sector A pointer to an uint16_t variable to store the calculated sector value.
 *
 * @throws None
 */
void lba_2_chs(uint32_t lba, uint16_t* cyl, uint16_t* head, uint16_t* sector){
    *cyl = lba / (2 * FLOPPY_144_SECTORS_PER_TRACK);
    *head   = ((lba % (2 * FLOPPY_144_SECTORS_PER_TRACK)) / FLOPPY_144_SECTORS_PER_TRACK);
    *sector = ((lba % (2 * FLOPPY_144_SECTORS_PER_TRACK)) % FLOPPY_144_SECTORS_PER_TRACK + 1);
}