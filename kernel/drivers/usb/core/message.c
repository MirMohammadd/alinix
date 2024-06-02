/**
 * @author Ali Mirmohammad
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


/**
 * Callback function called when a USB API operation completes.
 *
 * This function is a callback function that is called when a USB API operation completes.
 * It takes a pointer to a `urb` (USB Request Block) structure as input.
 * Inside the function, it retrieves the `api_context` structure from the `urb` and updates its `status` field with the status of the completed operation.
 *
 * @param urb A pointer to the `urb` (USB Request Block) structure.
 *
 * @return void
 *
 * @throws None
 */
static void usb_api_blocking_completion(struct urb *urb){
    struct api_context *ctx = urb->context;
    ctx->status = urb->status;

}

/**
 * Starts a USB URB and waits for it to complete.
 *
 * This function starts a USB URB (USB Request Block) and waits for it to complete.
 * It takes a pointer to a `urb` structure, a timeout value, and a pointer to an `actual_length` variable as input parameters.
 * Inside the function, it initializes the `api_context` structure, sets the `actual_length` field of the `urb` structure to 0,
 * and assigns the address of the `api_context` structure to the `context` field of the `urb` structure.
 *
 * @param urb A pointer to the `urb` structure.
 * @param timeout The timeout value in milliseconds. If set to 0, the function will wait indefinitely.
 * @param actual_length A pointer to an integer variable that will store the actual length of the completed URB.
 *
 * @return 0 if the URB completed successfully, or an error code if there was an error.
 *
 * @throws None
 */
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

/**
 * Sends a USB control message to a USB device.
 *
 * This function sends a USB control message to a USB device.
 * It takes various parameters such as the USB device, endpoint, request, request type, value, index,
 * driver data, size, timeout, and memory flags.
 * Inside the function, it allocates memory for the data buffer and checks if the allocation was successful.
 *
 * @param dev A pointer to the USB device.
 * @param endpoint The endpoint to send the control message to.
 * @param request The USB control request.
 * @param requesttype The type of the USB control request.
 * @param value The value associated with the USB control request.
 * @param index The index associated with the USB control request.
 * @param driver_data A pointer to the driver data to be sent with the control message.
 * @param size The size of the driver data.
 * @param timeout The timeout value in milliseconds. If set to 0, the function will wait indefinitely.
 * @param memflags The memory flags for memory allocation.
 *
 * @return 0 if the control message was sent successfully, or an error code if there was an error.
 *
 * @throws -ENOMEM if memory allocation fails.
 */
int usb_control_msg_send(struct usb_device *dev, u8 endpoint, u8 request,
			 u8 requesttype, u16 value, u16 index,
			 const void *driver_data, u16 size, int timeout,
			 gfp_t memflags){
        int ret;
        u8 *data = NULL;
        if (!data)
			return -ENOMEM;

        }