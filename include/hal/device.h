
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
 * @file device.h

 */
#ifndef DEVICE_H
#define DEVICE_H

#include <fs/vfs.h>
#include <fs/fat_mount.h>

typedef struct device {
    int id;
    int type; // 0 floppy, 1 ata hdd
    char mount[4];
    char* (*read) (int lba);
    int (*write) (int lba);
    filesystem fs;
    fat_mount_info_t minfo;
} device_t;

void device_register(device_t *dev);
device_t *get_dev_by_name(char *name);
device_t *get_dev_by_id(int id);
int get_dev_id_by_name(char *name);

#endif