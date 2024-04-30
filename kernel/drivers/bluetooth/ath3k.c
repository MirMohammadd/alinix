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

#include <alinix/kernel.h>
#include "bluetooth.h"
#include "btbcm.h"
#include "hci_core.h"

/**
 * @ref https://github.com/torvalds/linux/blob/master/drivers/bluetooth/ath3k.c
*/

#define VERSION "1.0"
#define ATH3K_FIRMWARE	"ath3k-1.fw"

#define ATH3K_DNLOAD				0x01
#define ATH3K_GETSTATE				0x05
#define ATH3K_SET_NORMAL_MODE			0x07
#define ATH3K_GETVERSION			0x09
#define USB_REG_SWITCH_VID_PID			0x0a

#define ATH3K_MODE_MASK				0x3F
#define ATH3K_NORMAL_MODE			0x0E

#define ATH3K_PATCH_UPDATE			0x80
#define ATH3K_SYSCFG_UPDATE			0x40

#define ATH3K_XTAL_FREQ_26M			0x00
#define ATH3K_XTAL_FREQ_40M			0x01
#define ATH3K_XTAL_FREQ_19P2			0x02
#define ATH3K_NAME_LEN				0xFF

#define REVERSED_LEN 7

struct ath3k_version{
    /*Structure that define the version attributes*/
    u8 rom_version;
    int build_version;
    int ran_version;
    u8 ref_clock;
    u8 revered[REVERSED_LEN];
};