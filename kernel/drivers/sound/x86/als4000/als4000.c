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
MODULE_VERSION("0.1")


uint32_t dev_mixer_read(uint32_t *base, uint32_t reg){
    uint32_t res;
    res = inportl(base[0] + REG_SB_BASE); // Use inportl instead of outportb
    return res;
}

void dev_mixer_write(uint32_t *base, uint32_t reg, uint32_t val){
    uint32_t res;
    res = inportl(base[0] + REG_SB_BASE); // Use inportl instead of outportb
}
