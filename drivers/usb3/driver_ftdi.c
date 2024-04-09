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
 * @file driver_ftdi.c

 */

#pragma message("Starting to compile "__FILE__)

#include <io.h>
#include <driver.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>

#define FTDI_VENDOR_ID                    0x0403

#define FTDI_PRODUCT_ID_FT232R            0x6001
#define FTDI_PRODUCT_ID_FT232R_FAKE       0x0000
#define FTDI_PRODUCT_ID_FT232RL           0xFBFA
#define FTDI_PRODUCT_ID_FT2232            0x6010
#define FTDI_PRODUCT_ID_FT4232H           0x6011
#define FTDI_PRODUCT_ID_FT232H            0x6014
#define FTDI_PRODUCT_ID_FT231X            0x6015
#define FTDI_PRODUCT_ID_STK500            0xfa33
#define FTDI_PRODUCT_ID_OPENMOKO          0x5118 /* FT2232 */
#define FTDI_PRODUCT_ID_TUMPA             0x8A98 /* FT2232 */
#define FTDI_PRODUCT_ID_KTLINK            0xBBE2 /* FT2232 */
#define FTDI_PRODUCT_ID_JTAGKEY           0xCFF8 /* FT2232 */

#define FTDI_SIO_RESET                    0
#define FTDI_SIO_MODEM_CTRL               1
#define FTDI_SIO_SET_BAUD_RATE            3
#define FTDI_SIO_SET_CONFIG               4

#define FTDI_SIO_RESET_PURGE_RX           1
#define FTDI_SIO_RESET_PURGE_TX           2

#define FTDI_SIO_SET_DTR_MASK             0x1
#define FTDI_SIO_SET_DTR_HIGH             (1 | (FTDI_SIO_SET_DTR_MASK << 8))
#define FTDI_SIO_SET_DTR_LOW              (0 | (FTDI_SIO_SET_DTR_MASK << 8))
#define FTDI_SIO_SET_RTS_MASK             0x2
#define FTDI_SIO_SET_RTS_HIGH             (2 | (FTDI_SIO_SET_RTS_MASK << 8))
#define FTDI_SIO_SET_RTS_LOW              (0 | (FTDI_SIO_SET_RTS_MASK << 8))

#define FTDI_DEVICE_IN_REQTYPE            LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE | 0x80
#define FTDI_DEVICE_OUT_REQTYPE           LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE

#define FTDI_MODEM_STATUS_BYTES_COUNT     2

#define FTDI_PARITY_CONFIG_VALUE_SHIFT    8
#define FTDI_STOP_BITS_CONFIG_VALUE_SHIFT 11

#define FTDI_PARITY_NONE_CONFIG_VALUE     (0x00 << FTDI_PARITY_CONFIG_VALUE_SHIFT)
#define FTDI_PARITY_ODD_CONFIG_VALUE      (0x01 << FTDI_PARITY_CONFIG_VALUE_SHIFT)
#define FTDI_PARITY_EVEN_CONFIG_VALUE     (0x02 << FTDI_PARITY_CONFIG_VALUE_SHIFT)
#define FTDI_PARITY_MARK_CONFIG_VALUE     (0x03 << FTDI_PARITY_CONFIG_VALUE_SHIFT)
#define FTDI_PARITY_SPACE_CONFIG_VALUE    (0x04 << FTDI_PARITY_CONFIG_VALUE_SHIFT)

#define FTDI_STOP_BITS_1_CONFIG_VALUE     (0x00 << FTDI_STOP_BITS_CONFIG_VALUE_SHIFT)
#define FTDI_STOP_BITS_1_5_CONFIG_VALUE   (0x01 << FTDI_STOP_BITS_CONFIG_VALUE_SHIFT)
#define FTDI_STOP_BITS_2_CONFIG_VALUE     (0x02 << FTDI_STOP_BITS_CONFIG_VALUE_SHIFT)

#define FTDI_SET_MODEM_CTRL_DEFAULT1      0x0101

#define FTDI_READ_ENDPOINT(i)             (0x81 + 2 * i)
#define FTDI_WRITE_ENDPOINT(i)            (0x02 + 2 * i)

static const char* FTDI_DEVICE_NAME_FT232R   = "FT232R";
static const char* FTDI_DEVICE_NAME_FT232RL  = "FT232RL";
static const char* FTDI_DEVICE_NAME_FT2232   = "FT2232";
static const char* FTDI_DEVICE_NAME_FT4232H  = "FT4232H";
static const char* FTDI_DEVICE_NAME_FT232H   = "FT232H";
static const char* FTDI_DEVICE_NAME_FT231X   = "FT231X";
static const char* FTDI_DEVICE_NAME_STK500   = "STK500";
static const char* FTDI_DEVICE_NAME_OPENMOKO = "OPENMOKO";
static const char* FTDI_DEVICE_NAME_TUMPA    = "TUMPA";
static const char* FTDI_DEVICE_NAME_KTLINK   = "KTLINK";
static const char* FTDI_DEVICE_NAME_JTAGKEY  = "JTAGKEY";
static const char* FTDI_DEVICE_NAME_GENERIC  = "FTDI";

enum fdti_device_types{
    FTDI_DEVICE_TYPE_423H,
    FTDI_DEVICE_TYPE_2232,
    FTDI_DEVICE_TYPE_232H,
    FTDI_DEVICE_TYPE_OTHER
};


struct fdti_data{
    enum fdti_device_types device_type;
    uint16_t control_idx;
    size_t max_packet_size;
};

struct ftdi_baud_data{
    int baud;
    uint16_t value;
};

// Baud rates values
static const struct ftdi_baud_data baud_lookup_table [] = 
{
    { 300,     0x2710 },
    { 600,     0x1388 },
    { 1200,    0x09c4 },
    { 2400,    0x04e2 },
    { 4800,    0x0271 },
    { 9600,    0x4138 },
    { 19200,   0x809c },
    { 38400,   0xc04e },
    { 57600,   0x0034 },
    { 115200,  0x001a },
    { 230400,  0x000d },
    { 460800,  0x4006 },
    { 921600,  0x8003 },
    { 0,       0x0000 }
};


static const struct ftdi_baud_data* ftdi_serial_baud(int baud){
    const struct ftdi_baud_data *map = baud_lookup_table;

    while (map->baud){
        if (map->baud == baud) return map;
        map++;

    return NULL;
    }
}

static inline ftdi_ctrl(struct usbserial_port *port,uint16_t req,uint16_t sio,uint16_t control_idx){
    return libusb_control_transfer(
                port->usb_dev_hdl,
                FTDI_DEVICE_OUT_REQTYPE,
                req,
                sio,
                control_idx,
                NULL,
                0,
            DEFAULT_CONTROL_TIMEOUT_MILLIS);
}

int ftdi_check_supported_by_vid_pid(uint16_t vid,uint16_t pid){
    if (FTDI_VENDOR_ID != vid)
        return NULL;

    switch (pid){
    case FTDI_PRODUCT_ID_FT232R:
    case FTDI_PRODUCT_ID_FT232R_FAKE:
    case FTDI_PRODUCT_ID_FT232RL:
    case FTDI_PRODUCT_ID_FT2232:
    case FTDI_PRODUCT_ID_FT4232H:
    case FTDI_PRODUCT_ID_FT231X:
    case FTDI_PRODUCT_ID_FT232H:
    case FTDI_PRODUCT_ID_STK500:
    case FTDI_PRODUCT_ID_OPENMOKO:
    case FTDI_PRODUCT_ID_TUMPA:
    case FTDI_PRODUCT_ID_KTLINK:
    case FTDI_PRODUCT_ID_JTAGKEY:
    ////////////////////////////
        return 1;
    default:
        return 0;
    }
}

static const char* ftdi_get_device_name(uint16_t vid,uint16_t pid,uint8_t classes,uint8_t subclasses){
    assert(FTDI_VENDOR_ID == vid);
        switch (pid)
    {
    case FTDI_PRODUCT_ID_FT232R:
    case FTDI_PRODUCT_ID_FT232R_FAKE: return FTDI_DEVICE_NAME_FT232R;
    case FTDI_PRODUCT_ID_FT2232: return FTDI_DEVICE_NAME_FT2232;
    case FTDI_PRODUCT_ID_FT4232H: return FTDI_DEVICE_NAME_FT4232H;
    case FTDI_PRODUCT_ID_FT232H: return FTDI_DEVICE_NAME_FT232H;        
    case FTDI_PRODUCT_ID_FT231X: return FTDI_DEVICE_NAME_FT231X;
    case FTDI_PRODUCT_ID_FT232RL: return FTDI_DEVICE_NAME_FT232RL;
    case FTDI_PRODUCT_ID_STK500: return FTDI_DEVICE_NAME_STK500;
    case FTDI_PRODUCT_ID_OPENMOKO: return FTDI_DEVICE_NAME_OPENMOKO;
    case FTDI_PRODUCT_ID_TUMPA: return FTDI_DEVICE_NAME_TUMPA;
    case FTDI_PRODUCT_ID_KTLINK: return FTDI_DEVICE_NAME_KTLINK;
    case FTDI_PRODUCT_ID_JTAGKEY: return FTDI_DEVICE_NAME_JTAGKEY;

    default: return FTDI_DEVICE_NAME_GENERIC;
    }
}

static unsigned int ftdi_get_ports_count(uint16_t vid,uint16_t pid){
    assert(FTDI_VENDOR_ID == vid);

    switch (pid)
    {
    case FTDI_PRODUCT_ID_OPENMOKO:
    case FTDI_PRODUCT_ID_TUMPA:
    case FTDI_PRODUCT_ID_KTLINK:
    case FTDI_PRODUCT_ID_JTAGKEY:
    case FTDI_PRODUCT_ID_FT2232: return 2;
    case FTDI_PRODUCT_ID_FT4232H: return 4;

    default: return 1;
    }
}

#pragma message("Finished compiling: " __FILE__)