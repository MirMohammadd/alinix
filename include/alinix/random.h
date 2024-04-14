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
 * @file random.h

 */
#ifndef __ALINIX_KERNEL_RANDOM_HEADER_H
#define __ALINIX_KERNEL_RANDOM_HEADER_H

#include <alinix/types.h>

static uint32_t next;

static int Next(uint32_t max );
static int Next(uint32_t min, uint32_t max);             
static void SetSeed(uint32_t seed);

#endif /*__ALINIX_KERNEL_RANDOM_HEADER_H*/