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
 * @file driver_cdc.c

 */

#include <io.h>
#include <driver.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_endian.h>


/**
 * @brief Let's define some useful macros for the  CDC driver.
*/

#define ARDUINO_VENDOR_ID            0x2341
#define QINHENG_VENDOR_ID            0x1A86

#define CDC_DEVICE_CH9102F           0x55D4

#define CDC_DEVICE_CLASS             0x02
#define CDC_ACM_DEVICE_SUBCLASS      0x02

#define CDC_REQTYPE_HOST2DEVICE      0x21
#define CDC_REQTYPE_DEVICE2HOST      0xA1

#define CDC_REQ_SET_LINE_CODING      0x20
#define CDC_REQ_GET_LINE_CODING      0x21
#define CDC_REQ_SET_LINE_CONTROL     0x22

#define CDC_CONTROL_LINE_STATE_RTS   0x2
#define CDC_CONTROL_LINE_STATE_DTR   0x1

#define USB_CLASS_CDC_DATA           0x0a

static const char* CDC_DEVICE_NAME_ARDUINO = "CDC Arduino";
static const char* CDC_DEVICE_NAME_QINHENG = "CDC Qinheng";
static const char* CDC_DEVICE_NAME_CDC_ACM = "CDC";


static inline int cdc_ctrl(struct usbserial_port *port,uint16_t req,uint16_t value,void *data,uint16_t size){
    return libusb_control_transfer(
            port->usb_dev_hdl,
            CDC_REQTYPE_HOST2DEVICE,
            req,
            value,
            0,
            data,
            size,
            DEFAULT_CONTROL_TIMEOUT_MILLIS);
}

static int cdc_set_dtr_rts(struct usbsrial_port *port,
int dtr,
int rts){
    
}