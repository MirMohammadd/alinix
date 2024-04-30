#include <alinix/kernel.h>
#include <alinix/types.h>
#include <alinix/usb.h>



int usb_control_msg_send(struct usb_device *dev, u8 endpoint, u8 request,
			 u8 requesttype, u16 value, u16 index,
			 const void *driver_data, u16 size, int timeout,
			 gfp_t memflags){
        int ret;
        u8 *data = NULL;
        if (!data)
			return -ENOMEM;

        }