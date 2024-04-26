/**
 * @author Ali Mirmohammad
 * @file power_supply.h
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

#ifndef __ALINIX_KERNEL_POWER_SUPPLY_H
#define __ALINIX_KERNEL_POWER_SUPPLY_H

#include <alinix/types.h>


struct power_supply_battery_ocv_table{
    int ocv; // capacity
    int capacity; // microvolt 
};


struct power_supply_resistance_temp_table {
	int temp;	/* celsius */
	int resistance;	/* internal resistance percent */
};

struct power_supply_vbat_ri_table {
	int vbat_uv;	/* Battery voltage in microvolt */
	int ri_uohm;	/* Internal resistance in microohm */
};



#endif /*__ALINIX_KERNEL_POWER_SUPPLY_H*/