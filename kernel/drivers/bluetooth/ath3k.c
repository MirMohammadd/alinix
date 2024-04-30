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
#include <alinix/firmware.h>
#include "bluetooth.h"
#include "btbcm.h"
#include "hci_core.h"
#include "mod_devicetable.h"
#include <alinix/memory.h>
#include <alinix/ulib.h>
#include <alinix/usb.h>


/**
 * @ref https://github.com/torvalds/linux/blob/master/drivers/bluetooth/ath3k.c
*/

#define ENOMEM 12
#define BULK_SIZE 1024 // Buffer to allocate size
#define BUFSIZ 1024

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

static const struct usb_device_id ath3k_table[] = {
    {0x0CF3, 0x3000},
    {0x0489, 0xE027 },
	{0x0489, 0xE03D },
	{0x04F2, 0xAFF1 },
	{0x0930, 0x0215 },
	{0x0CF3, 0x3002 },
	{0x0CF3, 0xE019 },
	{0x13d3, 0x3304 },

	/* Atheros AR9285 Malbec with sflash firmware */
	{0x03F0, 0x311D },

	/* Atheros AR3012 with sflash firmware*/
	{0x0489, 0xe04d },
	{0x0489, 0xe04e },
	{0x0489, 0xe057 },
	{0x0489, 0xe056 },
	{0x0489, 0xe05f },
	{0x0489, 0xe076 },
	{0x0489, 0xe078 },
	{0x0489, 0xe095 },
	{0x04c5, 0x1330 },
	{0x04CA, 0x3004 },
	{0x04CA, 0x3005 },
	{0x04CA, 0x3006 },
	{0x04CA, 0x3007 },
	{0x04CA, 0x3008 },
	{0x04CA, 0x300b },
	{0x04CA, 0x300d },
	{0x04CA, 0x300f },
	{0x04CA, 0x3010 },
	{0x04CA, 0x3014 },
	{0x04CA, 0x3018 },
	{0x0930, 0x0219 },
	{0x0930, 0x021c },
	{0x0930, 0x0220 },
	{0x0930, 0x0227 },
	{0x0b05, 0x17d0 },
	{0x0CF3, 0x0036 },
	{0x0CF3, 0x3004 },
	{0x0CF3, 0x3008 },
	{0x0CF3, 0x311D },
	{0x0CF3, 0x311E },
	{0x0CF3, 0x311F },
	{0x0cf3, 0x3121 },
	{0x0CF3, 0x817a },
	{0x0CF3, 0x817b },
	{0x0cf3, 0xe003 },
	{0x0CF3, 0xE004 },
	{0x0CF3, 0xE005 },
	{0x0CF3, 0xE006 },
	{0x13d3, 0x3362 },
	{0x13d3, 0x3375 },
	{0x13d3, 0x3393 },
	{0x13d3, 0x3395 },
	{0x13d3, 0x3402 },
	{0x13d3, 0x3408 },
	{0x13d3, 0x3423 },
	{0x13d3, 0x3432 },
	{0x13d3, 0x3472 },
	{0x13d3, 0x3474 },
	{0x13d3, 0x3487 },
	{0x13d3, 0x3490 },

	/* Atheros AR5BBU12 with sflash firmware */
	{0x0489, 0xE02C },

	/* Atheros AR5BBU22 with sflash firmware */
	{0x0489, 0xE036 },
	{0x0489, 0xE03C },

	{ }	/* Terminating entry */
};

#define BTUSB_ATH3012		0x80

static const struct usb_device_id ath3k_blist_tbl[] = {

	/* Atheros AR3012 with sflash firmware*/
	{ 0x0489, 0xe04e, .driver_info = BTUSB_ATH3012 },
	{ 0x0489, 0xe04d, .driver_info = BTUSB_ATH3012 },
	{ 0x0489, 0xe056, .driver_info = BTUSB_ATH3012 },
	{ 0x0489, 0xe057, .driver_info = BTUSB_ATH3012 },
	{ 0x0489, 0xe05f, .driver_info = BTUSB_ATH3012 },
	{ 0x0489, 0xe076, .driver_info = BTUSB_ATH3012 },
	{ 0x0489, 0xe078, .driver_info = BTUSB_ATH3012 },
	{ 0x0489, 0xe095, .driver_info = BTUSB_ATH3012 },
	{ 0x04c5, 0x1330, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x3004, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x3005, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x3006, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x3007, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x3008, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x300b, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x300d, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x300f, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x3010, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x3014, .driver_info = BTUSB_ATH3012 },
	{ 0x04ca, 0x3018, .driver_info = BTUSB_ATH3012 },
	{ 0x0930, 0x0219, .driver_info = BTUSB_ATH3012 },
	{ 0x0930, 0x021c, .driver_info = BTUSB_ATH3012 },
	{ 0x0930, 0x0220, .driver_info = BTUSB_ATH3012 },
	{ 0x0930, 0x0227, .driver_info = BTUSB_ATH3012 },
	{ 0x0b05, 0x17d0, .driver_info = BTUSB_ATH3012 },
	{ 0x0CF3, 0x0036, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0x3004, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0x3008, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0x311D, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0x311E, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0x311F, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0x3121, .driver_info = BTUSB_ATH3012 },
	{ 0x0CF3, 0x817a, .driver_info = BTUSB_ATH3012 },
	{ 0x0CF3, 0x817b, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0xe004, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0xe005, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0xe006, .driver_info = BTUSB_ATH3012 },
	{ 0x0cf3, 0xe003, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3362, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3375, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3393, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3395, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3402, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3408, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3423, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3432, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3472, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3474, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3487, .driver_info = BTUSB_ATH3012 },
	{ 0x13d3, 0x3490, .driver_info = BTUSB_ATH3012 },

	/* Atheros AR5BBU22 with sflash firmware */
	{ 0x0489, 0xE036, .driver_info = BTUSB_ATH3012 },
	{ 0x0489, 0xE03C, .driver_info = BTUSB_ATH3012 },

	{ }	/* Terminating entry */
};

PRIVATE __always_inline VOID ath3k_log_failed_loading(int err,int len,int size,int count){
    perror("Firmware loading err = %d, len %d size = %d, count = %d",err,len,size,count);
}

#define USB_REQ_DFU_DNLOAD	1
#define BULK_SIZE		4096
#define FW_HDR_SIZE		20
#define TIMEGAP_USEC_MIN	50
#define TIMEGAP_USEC_MAX	100

static int ath3k_load_firmware(struct usb_device *udev,const struct firmware* firmware){
    ////////////////////////////////
    // Sending buffer
    u8 *sendBuf;
    int len = 0;
    int err, pipe, size, sent = 0;
	int count = firmware->size;
    ////////////////////////////////
    print("udev %d",udev);

    sendBuf = (u8 *)malloc(BUFSIZ);

    if (!sendBuf){
        print("Can't allocate memory chunk for firmware");
        return -ENOMEM;

    }
}