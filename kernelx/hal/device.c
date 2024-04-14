
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
 * @file device.c

 */


#include <hal/device.h>
#include <lib/string.h>
#include <fs/vfs.h>
#include <drivers/video.h>

static device_t *devices[8];


void device_registerO(device_t *dev){
    if (dev->id < 8){
        devices[dev->id] = dev;
        vfs_mount(dev->mount);
    }
}

device_t *get_dev_by_name(char *name) {
    if(name[0] == '/')
        name++;
    for(int i = 0; i < 8; i++) {
        if(strncmp(devices[i]->mount, name, 3) == 0)
            return devices[i];
    }
    return NULL;
}


device_t *get_dev_by_id(int id) {
    for(int i = 0; i < 8; i++) {
        if(devices[i]->id == id)
            return devices[i];
    }
    return NULL;
}


int get_dev_id_by_name(char *name) {
    if(name[0] == '/')
        name++;
    for(int i = 0; i < 8; i++) {
        if(strncmp(devices[i]->mount, name, 3) == 0)
            return devices[i]->id;
    }
    return -1;
}