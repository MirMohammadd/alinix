/**
 * @author Ali Mirmohammad
 * @file adc-keys.c
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
 *  - Util over the keyboard keys.
*/

#include <alinix/err.h>
#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/iio/trigger.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Keyboard module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


struct adc_keys_button{
    u32 voltage;
    u32 keycode;
};


struct dc_keys_state{
    struct iio_channel *channel;
    u32 num_keys;
    u32 last_key;
    u32 keyup_voltage;
    const struct adc_keys_button *map;
};

