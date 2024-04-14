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
 * @file memory.h

 */
#ifndef _ALINIX_KERNEL_MEMORY_H
#define _ALINIX_KERNEL_MEMORY_H

#include <alinix/types.h>

void memset(void* bufptr, char value, uint32_t size);
void memcpy(void* dstptr, const void* srcptr, uint32_t size);
int memcmp(const void* aptr, const void* bptr, uint32_t size);
void * memmove(void* dstptr, const void* srcptr, uint32_t size);

#endif /*_ALINIX_KERNEL_MEMORY_H*/