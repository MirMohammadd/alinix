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
 * @file mm.h

 */

#ifndef MM_H
#define MM_H

#include <types.h>


#define BLOCK_PER_BYTE 8


#define BLOCKS_LEN 4096
#define BYTE_SET 0xFFFFFFFF
#define BITMAP_LEN 0x8000


#define KERNEL_SPACE_END 0x401000


typedef uint32_t mm_addr_t;
typedef uint32_t mm_addr_t;


typedef struct mem_info{
    uint32_t size;
    uint32_t used_blocks;
    uint32_t max_blocks;
    mm_addr_t *map;
}mem_info_t;


typedef struct memory_region {
    uint32_t size;
    uint32_t addr_low;
    uint32_t addr_high;
    uint32_t len_low;
    uint32_t len_high;
    uint32_t type;
} __attribute__((__packed__)) mem_region_t;



#endif