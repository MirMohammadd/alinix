/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg
 * @file core.c

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

