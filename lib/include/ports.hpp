#pragma once

#include "types.h"

#ifdef __cplusplus
using namespace LIBHeisenKernel;
#endif

void mmio_outb(dword_t base, byte_t value);
void mmio_outw(dword_t base, word_t value);
void mmio_outd(dword_t base, dword_t value);
byte_t mmio_inb(dword_t base);
word_t mmio_inw(dword_t base);
dword_t mmio_ind(dword_t base);
