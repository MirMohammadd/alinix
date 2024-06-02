/**
 * @author Ali Mirmohammad
 * @file usb.c
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
 *  - Implements the USB drivers.
*/

#include <alinix/kernel.h>
#include <alinix/usb.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("USB driver")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

/**
 * @brief Kills a URB (USB Request Block) by cancelling its associated USB transfer.
 *
 * This function cancels the USB transfer associated with the provided URB (USB Request Block).
 * It checks if the URB and the associated USB device are valid, and if so, it calls the
 * USB host controller driver's `usb_hcd_unlink_urb` function to cancel the transfer.
 *
 * @param urb A pointer to the URB to be killed.
 *
 * @return This function does not return a value.
 *
 * @note The function assumes that the URB is associated with a USB device.
 *
 * @example
 * struct urb *urb = ...; // Example URB
 *
 * usb_kill_urb(urb);
 */
void usb_kill_urb(struct urb *urb){
    if (!(urb && urb->dev)){
        return;
    }
    
}