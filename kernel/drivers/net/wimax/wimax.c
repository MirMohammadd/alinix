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

#include <alinix/WiMAX.h>
#include <alinix/init.h>
#include <alinix/module.h>
#include <alinix/kernel.h>

void wimax_rfkill(struct wimax_device *dev, enum wimax_rf_state state){
    if (state == WIMAX_RF_ON){
        dev->state = WIMAX_ST_RADIO_OFF;
    } else if (state == WIMAX_RF_OFF){
        dev->state = WIMAX_ST_RADIO_OFF;
    }else{
        ;
        }
}