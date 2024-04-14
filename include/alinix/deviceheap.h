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
 * @file deviceheap.h
 */
#ifndef __ALINIX_KERNEL_DEVICE_HEAP_H   
#define __ALINIX_KERNEL_DEVICE_HEAP_H

#include <alinix/types.h>

#define DEVICE_HEAP_SIZE 100_MB

#define DEVICE_HEAP_START (KERNEL_HEAP_START + KERNEL_HEAP_SIZE + 4_MB)
#define DEVICE_HEAP_END (DEVICE_HEAP_START + DEVICE_HEAP_SIZE)


// Current address of last memory allocation
// Will increase on every allocation
static uint32_t currentAddress;

// Allocate a chunck of memory in the virtual address space
// Must be a page aligned size
// Note: Memory needs to be mapped to right address afterwards, function does not include this
uint32_t AllocateChunk(uint32_t size);


#endif /*__ALINIX_KERNEL_DEVICE_HEAP_H*/