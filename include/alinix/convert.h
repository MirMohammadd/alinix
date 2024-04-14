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
 * @file convert.h
 */
#ifndef __ALINIX_KERNEL_CONVERT_HEADER_H
#define __ALINIX_KERNEL_CONVERT_HEADER_H

#include <alinix/types.h>

int isspace(char c);

char* IntToString(int n);

char*IntToString32(uint32_t n);

char* IntToHexString(uint8_t w);

int StringToInt(char* string);

uint32_t HexToInt(char* string);

#endif /*__ALINIX_KERNEL_CONVERT_HEADER_H*/