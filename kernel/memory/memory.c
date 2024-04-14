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
 * @file memory.c

 */
#include <alinix/memory.h>

void memset(void* bufptr, char value, uint32_t size){
    unsigned char* buf = (unsigned char*)bufptr;

    for (uint32_t i = 0;i < size;i++){
        buf[i] = (unsigned char)value;
    }
    return bufptr;
}

int memcmp(const void* aptr, const void* bptr, uint32_t size){
    const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (uint32_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}

void* memmove(void* dstptr, const void* srcptr, uint32_t size){
    unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (uint32_t i = 0; i < size; i++)
			dst[i] = src[i];
	} else {
		for (uint32_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}

void* memcpy(void* dstptr, const void* srcptr, uint32_t size){
    unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (uint32_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}