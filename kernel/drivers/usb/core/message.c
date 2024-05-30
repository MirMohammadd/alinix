/**
 * @file message.c
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
 *  - Not implemented yet.
 *  - Message util of the kernel (USB).
*/
#include <alinix/kernel.h>
#include <alinix/types.h>
#include <alinix/usb.h>
#include <alinix/completion.h>
#include <alinix/jiffies.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("USB kernel module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")



static void  cancel_async_set_config(struct usb_device *udev);

struct api_context{
    struct completion    done;
    int                 status;
};


static void usb_api_blocking_completion(struct urb *urb){
    struct api_context *ctx = urb->context;
    ctx->status = urb->status;

}

static int usb_start_wait_urb(struct urb *urb, int timeout, int *actual_length){
    struct api_context ctx;
    unsigned long expire;
    int retval;
    urb->context = &ctx;
    urb->actual_length = 0;

    if (unlikely(retval)){
        goto out;
    }
    expire = timeout ? msecs_to_jiffies(timeout): MAX_SCHEDULE_TIMEOUT;

    out:

}

int usb_control_msg_send(struct usb_device *dev, u8 endpoint, u8 request,
			 u8 requesttype, u16 value, u16 index,
			 const void *driver_data, u16 size, int timeout,
			 gfp_t memflags){
        int ret;
        u8 *data = NULL;
        if (!data)
			return -ENOMEM;

        }