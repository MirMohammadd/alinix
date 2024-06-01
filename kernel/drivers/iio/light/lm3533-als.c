/**
 * @author Ali Mirmohammad
 * @file lm3533-als.c
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
 * 	- Util for the light driver.
*/

#include <alinix/platform_device.h>
#include <alinix/mutex_types.h>
#include <alinix/types.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Light driver")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

#define LM3533_ALS_RESISTOR_MIN			1
#define LM3533_ALS_RESISTOR_MAX			127
#define LM3533_ALS_CHANNEL_CURRENT_MAX		2
#define LM3533_ALS_THRESH_MAX			3
#define LM3533_ALS_ZONE_MAX			4

#define LM3533_REG_ALS_RESISTOR_SELECT		0x30
#define LM3533_REG_ALS_CONF			0x31
#define LM3533_REG_ALS_ZONE_INFO		0x34
#define LM3533_REG_ALS_READ_ADC_RAW		0x37
#define LM3533_REG_ALS_READ_ADC_AVERAGE		0x38
#define LM3533_REG_ALS_BOUNDARY_BASE		0x50
#define LM3533_REG_ALS_TARGET_BASE		0x60

#define LM3533_ALS_ENABLE_MASK			0x01
#define LM3533_ALS_INPUT_MODE_MASK		0x02
#define LM3533_ALS_INT_ENABLE_MASK		0x01

#define LM3533_ALS_ZONE_SHIFT			2
#define LM3533_ALS_ZONE_MASK			0x1c

#define LM3533_ALS_FLAG_INT_ENABLED		1


struct lm3533_als {
	unsigned long flags;
	int irq;

	atomic_t zone;
	struct mutex thresh_mutex;
};

