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
 * @file error.c

 */

#include <libusbserial.h>
static const char* ERROR_MSG_UNSUPPORTED_OPERATION = "Unsupported operation";
static const char* ERROR_MSG_ILLEGAL_STATE = "Illegal state";
static const char* ERROR_MSG_INVALID_PARAMETER = "Invalid parameter";
static const char* ERROR_MSG_RESOURCE_ALLOC_FAILED = "Resource allocation failed";
static const char* ERROR_MSG_NO_SUCH_DEVICE = "No such device";
static const char* ERROR_MSG_UNSUPPORTED_DEVICE = "Unsupported device";
static const char* ERROR_MSG_UNSUPPORTED_BAUD_RATE = "Unsupported baud rate";
static const char* ERROR_MSG_INVALID_PORT_IDX = "Invalid port index";
static const char* ERROR_MSG_CTRL_CMD_FAILED = "Control command failed";

static const char* ERROR_MSG_UNKNOWN = "Unknown error";


const char* usbserial_get_error_str(int error_code){
    if (!error_code){
        return NULL;
    }

    if ((-1 >= error_code) && (-99 <= error_code)){
        return libusb_error_name(error_code);
    }

    switch (error_code){
        case USBSERIAL_ERROR_UNSUPPORTED_OPERATION  :
            return ERROR_MSG_UNSUPPORTED_OPERATION;
        
        case USBSERIAL_ERROR_ILLEGAL_STATE:
            return ERROR_MSG_ILLEGAL_STATE;
        
        case USBSERIAL_ERROR_INVALID_PARAMETER:
            return ERROR_MSG_INVALID_PARAMETER;
        
        case USBSERIAL_ERROR_RESOURCE_ALLOC_FAILED:
            return  ERROR_MSG_RESOURCE_ALLOC_FAILED;
        
        case USBSERIAL_ERROR_NO_SUCH_DEVICE:
            return ERROR_MSG_NO_SUCH_DEVICE;
        
        case USBSERIAL_ERROR_UNSUPPORTED_DEVICE:
            return ERROR_MSG_UNSUPPORTED_DEVICE;

        case USBSERIAL_ERROR_UNSUPPORTED_BAUD_RATE:
		return ERROR_MSG_UNSUPPORTED_BAUD_RATE;

        case USBSERIAL_ERROR_INVALID_PORT_IDX:
            return ERROR_MSG_INVALID_PORT_IDX;

        case USBSERIAL_ERROR_CTRL_CMD_FAILED:
            return ERROR_MSG_CTRL_CMD_FAILED;
        
        default:
            return ERROR_MSG_UNKNOWN;
    }
}