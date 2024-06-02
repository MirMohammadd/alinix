/**
 * @author Ali Mirmohammad
 * @file wimax.c
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
 *  - Kernel WIMAX driver for networking.
*/

#include <alinix/WiMAX.h>
#include <alinix/init.h>
#include <alinix/module.h>
#include <alinix/kernel.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel WIMAX driver for networking.")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

/**
 * Updates the radio state of a WiMAX device based on the provided RF state.
 *
 * @param dev A pointer to the WiMAX device structure.
 * @param state The desired RF state of the WiMAX device.
 *
 * @return None.
 *
 * @throws None.
 *
 * @details
 * This function updates the radio state of a WiMAX device based on the provided RF state.
 * It assumes that the `dev` parameter is a valid pointer to a WiMAX device structure.
 *
 * The function checks the value of the `state` parameter and updates the `dev->state`
 * member accordingly. If the `state` parameter is `WIMAX_RF_ON`, the `dev->state` member
 * is set to `WIMAX_ST_RADIO_OFF`. If the `state` parameter is `WIMAX_RF_OFF`, the `dev->state`
 * member is also set to `WIMAX_ST_RADIO_OFF`.
 *
 * If the `state` parameter is neither `WIMAX_RF_ON` nor `WIMAX_RF_OFF`, the function does
 * nothing.
 *
 * @note
 * This function assumes that the `WIMAX_RF_ON` and `WIMAX_RF_OFF` constants are defined and
 * represent the possible RF states of the WiMAX device. It also assumes that the `WIMAX_ST_RADIO_OFF`
 * constant is defined and represents the radio state when the WiMAX device is turned off.
 */
void wimax_rfkill(struct wimax_device *dev, enum wimax_rf_state state){
    if (state == WIMAX_RF_ON){
        dev->state = WIMAX_ST_RADIO_OFF;
    } else if (state == WIMAX_RF_OFF){
        dev->state = WIMAX_ST_RADIO_OFF;
    }else{
        ;
        }
}