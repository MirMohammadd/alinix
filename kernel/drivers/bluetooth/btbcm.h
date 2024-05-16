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

/**
 * @abstraction:
 * 	- Bluetooth header file for ath3k.c.
*/


#ifndef __ALINIX_KERNEL_BTB_CM_H
#define __ALINIX_KERNEL_BTB_CM_H

#define BCM_UART_CLOCK_48MHZ	0x01
#define BCM_UART_CLOCK_24MHZ	0x02

#include <alinix/types.h>
#include <alinix/compiler_attributes.h>
#include <alinix/compiler_types.h>

struct bcm_update_uart_baud_rate{
    u16 zero;
    u16 baud_rate;
};


struct bcm_write_uart_clock_setting{
    u8 type;
};


struct bcm_set_sleep_mode{
    u8 sleep_mode;
    u8 idle_host;
    u8 idle_dev;
    u8 bt_wake_active;
    u8 host_wake_active;
	u8 allow_host_sleep;
	u8 combine_modes;
	u8 tristate_control;
	u8 usb_auto_sleep;
	u8 usb_resume_timeout;
	u8 break_to_host;
	u8 pulsed_host_wake;
};


struct bcm_set_pcm_int_params {
	u8 routing;
	u8 rate;
	u8 frame_sync;
	u8 sync_mode;
	u8 clock_mode;
} ;

struct bcm_set_pcm_format_params {
	u8 lsb_first;
	u8 fill_value;
	u8 fill_method;
	u8 fill_num;
	u8 right_justify;
} ;

#ifdef CONFIG_BT_BCM

int btbcm_check_bdaddr(struct hci_dev *hdev);
int btbcm_set_bdaddr(struct hci_dev *hdev, const bdaddr_t *bdaddr);
int btbcm_patchram(struct hci_dev *hdev, const struct firmware *fw);
int btbcm_read_pcm_int_params(struct hci_dev *hdev,
			      struct bcm_set_pcm_int_params *params);
int btbcm_write_pcm_int_params(struct hci_dev *hdev,
			       const struct bcm_set_pcm_int_params *params);

int btbcm_setup_patchram(struct hci_dev *hdev);
int btbcm_setup_apple(struct hci_dev *hdev);

int btbcm_initialize(struct hci_dev *hdev, bool *fw_load_done, bool use_autobaud_mode);
int btbcm_finalize(struct hci_dev *hdev, bool *fw_load_done, bool use_autobaud_mode);


#else 


#endif

#endif