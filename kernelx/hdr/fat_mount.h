
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
 * @file fat_mount.h

 */
#ifndef FAT12_MOUNT_H
#define FAT12_MOUNT_H

#include <types.h>

typedef struct fat_mount_info {
    /* FS type
     * 0 = FAT12
     * 1 = FAT16
     * 2 = FAT32
     * 3 = EXFAT
     */
    int type;
    uint32_t n_sectors;
    uint32_t fat_offset;
    uint32_t n_root_entries;
    uint32_t root_offset;
    uint32_t root_size;
    uint32_t fat_size;
    uint32_t fat_entry_size;
    uint32_t first_data_sector;
    uint32_t data_sectors;
} fat_mount_info_t;

#endif