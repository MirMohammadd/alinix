
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
 * @file suspend_ioctls.h

 */
#ifndef __HEISEN_SUSPEND_IOCTLS_H
#define __HEISEN_SUSPEND_IOCTLS_H


#include <heisen/typing.h>

struct resume_swap_area {
	__kernel_loff_t offset;
	uint32_t dev;
} __attribute__((packed));



#endif // __HEISEN_SUSPEND_IOCTLS_H