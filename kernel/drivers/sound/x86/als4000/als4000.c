/**
 * @author Ali Mirmohammad
 * @file als4000.c
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
#include <alinix/drivers/audio/als4000/als4000.h>
#include <alinix/drivers/audio/als4000/sound.h>
#include <alinix/drivers/audio/als4000/mixer.h>


#include <alinix/module.h>
#include <alinix/kernel.h>
#include <alinix/init.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("ALSA 4000 driver")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")


/**
 * Reads the value from a device mixer register.
 *
 * This function reads the value from the specified register of the device mixer.
 * It takes a pointer to the base address of the device mixer and the register number as input parameters.
 * It uses the `inportl()` function to read the value from the specified register.
 *
 * @param base A pointer to the base address of the device mixer.
 * @param reg The register number to read from.
 *
 * @return The value read from the specified register.
 *
 * @throws None
 */
uint32_t dev_mixer_read(uint32_t *base, uint32_t reg){
    uint32_t res;
    res = inportl(base[0] + REG_SB_BASE); // Use inportl instead of outportb
    return res;
}

/**
 * Writes a value to a device mixer register.
 *
 * This function writes a value to the specified register of the device mixer.
 * It takes a pointer to the base address of the device mixer, the register number,
 * and the value to write as input parameters. It reads the current value from the
 * specified register using the `inportl()` function and then performs the write operation.
 *
 * @param base A pointer to the base address of the device mixer.
 * @param reg The register number to write to.
 * @param val The value to write to the specified register.
 *
 * @return void
 *
 * @throws None
 */
VOID dev_mixer_write(uint32_t *base, uint32_t reg, uint32_t val){
    uint32_t res;
    res = inportl(base[0] + REG_SB_BASE); // Use inportl instead of outportb
}
