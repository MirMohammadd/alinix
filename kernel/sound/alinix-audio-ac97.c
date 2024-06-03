/**
 * @author Ali Mirmohammad
 * @file alinix-audio-ac97.c
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
 *  - Kernel audio driver util.
*/
#include <alinix/alinix-audio-ac97.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/pci.h>
#include <alinix/interrupt.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("AC97 Audio Driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

/**
 * @brief Writes a value to the specified AC97 codec register.
 *
 * This function writes a value to the specified AC97 codec register. It takes three parameters:
 * - `reg`: The AC97 codec register to write to.
 * - `value`: The value to write to the register.
 * - `dev`: A pointer to the `struct ac97_codec` object representing the AC97 codec.
 *
 * The function performs the following steps:
 * 1. Writes the `value` to the specified `reg`ister of the AC97 codec by calling the `outportw` function.
 *
 * @param reg The AC97 codec register to write to.
 * @param value The value to write to the register.
 * @param dev A pointer to the `struct ac97_codec` object representing the AC97 codec.
 *
 * @note The function assumes that the `outportw` function is available for writing to the AC97 codec register.
 *
 * @example
 * struct ac97_codec* dev = ac97_init();
 * uint16_t reg = 0x10;
 * uint16_t value = 0x1234;
 *
 * ac97_write_register(reg, value, dev);
 */
static inline void ac97_write_register(uint16_t reg,uint16_t value,struct ac97_codec* dev){
    outportw(dev->base_address + reg,value);
}

/**
 * @brief Reads the value from the specified AC97 codec register.
 *
 * This function reads the value from the specified AC97 codec register. It takes two parameters:
 * - `reg`: The AC97 codec register to read from.
 * - `dev`: A pointer to the `struct ac97_codec` object representing the AC97 codec.
 *
 * The function performs the following steps:
 * 1. Reads the value from the specified `reg`ister of the AC97 codec by calling the `inportw` function.
 * 2. Returns the read value.
 *
 * @param reg The AC97 codec register to read from.
 * @param dev A pointer to the `struct ac97_codec` object representing the AC97 codec.
 *
 * @return The value read from the specified register.
 *
 * @note The function assumes that the `inportw` function is available for reading from the AC97 codec register.
 *
 * @example
 * struct ac97_codec* dev = ac97_init();
 * uint16_t reg = 0x10;
 *
 * uint16_t value = ac97_read_register(reg, dev);
 * printf("Value read from register 0x%02x: 0x%04x\n", reg, value);
 */
static inline uint16_t ac97_read_register(uint16_t reg,struct ac97_codec* dev){
    return inportw(dev->base_address + reg);
}

/**
 * @brief Initializes the AC97 codec.
 *
 * This function initializes the AC97 codec by performing the following steps:
 * 1. Writes a reset value to the AC97_RESET_REGISTER.
 * 2. Reads the vendor ID from the AC97_VENDOR_ID_REGISTER.
 * 3. Checks if the vendor ID is not equal to 0xFFFF. If it is not, sets the `initialized`
 *    flag of the `ac97Dev` structure to true. Otherwise, sets it to false.
 * 4. Writes a value of 0x0000 to the AC97_MASTER_VOLUME_REGISTER and AC97_PCM_OUT_VOLUME_REGISTER.
 * 5. Enables interrupts.
 *
 * @note The function assumes that the `ac97_write_register` and `ac97_read_register` functions
 *       are available for writing to and reading from the AC97 codec registers, respectively.
 *
 * @example
 * struct ac97_codec* ac97Dev = ac97_init();
 *
 * ac97_initialize(ac97Dev);
 */
void ac97_initialize(){
    struct ac97_codec* ac97Dev;
    ac97_write_register(AC97_RESET_REGISTER, 0,ac97Dev);
    uint16_t vendor_id = ac97_read_register(AC97_VENDOR_ID_REGISTER,ac97Dev);

    if (vendor_id != 0xFFFF){
        ac97Dev->initialized = true;
    }
    else {
        ac97Dev->initialized = false;
    }
        // Set master volume to maximum
    ac97_write_register(AC97_MASTER_VOLUME_REGISTER, 0x0000,ac97Dev);
    ac97_write_register(AC97_PCM_OUT_VOLUME_REGISTER, 0x0000,ac97Dev);
    EnableInterrupts();

}
