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

#include <libusbserial.h>
#include <config.h>

#include <driver.h>
#include <internal.h>

#include <assert.h>

#include <stdlib.h>

extern struct usbserial_driver *usbserial_driver_ftdi;
extern struct usbserial_driver *usbserial_driver_silabs;
extern struct usbserial_driver *usbserial_driver_ch34x;
extern struct usbserial_driver *usbserial_driver_pl2303;
extern struct usbserial_driver *usbserial_driver_cdc;


static const struct usbserial_driver* find_driver_for_usb_device(uint16_t vid,uint16_t pid,uint8_t class,uint8_t subclass){

    const struct usbserial_drivers* drivers[] = 
    {
        usbserial_driver_ftdi,
		usbserial_driver_silabs,
		usbserial_driver_ch34x,
		usbserial_driver_pl2303,
		usbserial_driver_cdc,
		NULL
    };

    const struct usbserial_driver **driver = drivers;

    while (*driver){
        if ((*driver)->check_supported_by_vid_pid && (*driver)->check_supported_by_vid_pid(vid,pid))
            return *driver;
        
        if ((*driver)->check_supported_by_class && (*driver)->check_supported_by_class(class,subclass))
            return *driver;

        driver++;
    }


}

int usbserial_is_device_supported(uint16_t vid, uint16_t pid, uint8_t class, uint8_t subclass){
    return !!find_driver_for_usb_device(vid, pid, class, subclass);
}

