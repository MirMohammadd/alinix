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
 * @file io.c

 */

#include <io.h>
#include <config.h>
#include <driver.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usbserial_io_default_read_transfer_callback(struct libusb_transfer* transfer){
    assert(transfer);

    int ret;

    struct usbserial_port *port = (struct usbserial_port*) transfer->user_data;

    ret = pthread_mutex_lock(&port->mutex);

    assert(0 == ret);

    
}