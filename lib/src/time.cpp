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
 * @file time.cpp

 */
#include <time.h>

#include <syscall.h>

using namespace LIBHeisenKernel;

void Time::Sleep(uint32_t ms)
{
    DoSyscall(SYSCALL_SLEEP_MS, ms);
}

uint64_t Time::Ticks()
{
    uint64_t r = 0;
    DoSyscall(SYSCALL_GET_TICKS, (uint32_t)&r);
    return r;
}