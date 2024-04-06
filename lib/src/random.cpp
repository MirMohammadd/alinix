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
 * @file random.cpp

 */
#include <random.h>

using namespace LIBHeisenKernel;

uint32_t next = 12;

int Random::Next(uint32_t max)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % (max+1);
}

int Random::Next(uint32_t min, uint32_t max)
{
    return Next(max-min) + min;
}

void Random::SetSeed(uint32_t seed)
{
    next = seed;
}