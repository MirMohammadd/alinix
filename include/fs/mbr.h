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
 * @file mbr.h

 */


#ifndef MBR_H
#define MBR_H

#include <types.h>


#define FAT12_SYSTEM_ID             0x1
#define FAT16_SYSTEM_ID             0x4
#define NTFS_SYSTEM_ID              0x7
#define FAT32_SYSTEM_ID             0xC //0xB



typedef struct partition {
    uint8_t bootable;
    uint8_t start_head;
    uint16_t start_sect_cyl;
    uint8_t sys_id;
    uint8_t end_head;
    uint16_t end_sect_cyl;
    uint32_t lba_start;
    uint32_t total_sectors;
} __attribute__((__packed__)) partition_t;


typedef struct mbr {
    uint8_t fill[436];
    uint8_t id[10];
    partition_t partition_table[4];
    uint8_t signature[2];
} __attribute__((__packed__)) mbr_t;



#endif // MBR_H