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
 * @file multiboot.h

 */

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <types.h>



#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_BOOTLOADER MAGIC 0x2BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00000003





typedef struct multiboot_info_header{
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
    uint32_t entry_addr;
    uint32_t mode_type;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
}__attribute__((__packed__)) multiboot_header_t;





typedef struct multiboot_info {
    uint32_t flags;
    uint32_t mem_low;
    uint32_t mem_high;
    uint32_t boot_dev;
    uint32_t cmdline;
    uint32_t module_count;
    uint32_t module_addr;
    uint32_t syms[4];
    uint32_t mmap_len;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
} __attribute__((__packed__)) multiboot_info_t;

#endif