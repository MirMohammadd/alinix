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

#include <io.h>
#include <driver.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

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