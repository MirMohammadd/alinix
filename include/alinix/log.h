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
 * @file log.h

 */
#ifndef __ALINIX__LOG_H
#define __ALINIX__LOG_H

#include <alinix/types.h>

#define LOG_SHOW_MS 1


//? Use typedef?
enum LogLevel
{
    Info,
    Warning,
    Error
};

void Log(enum LogLevel level, const char* __restrict__ format, ...);
void Print(const char* data, uint32_t length);

#endif /*__ALINIX__LOG_H*/