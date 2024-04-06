#include <ports.hpp>
#include <types.h>

using namespace LIBHeisenKernel;

dword_t mmio_ind(dword_t base){
    dword_t *mem = (dword_t*)(base);
    return *mem;
}

void mmio_outb(dword_t base, byte_t value) {
 byte_t *mem = (byte_t *) (base);
 *mem = value;
}

void mmio_outw(dword_t base, word_t value) {
 word_t *mem = (word_t *) (base);
 *mem = value;
}

void mmio_outd(dword_t base, dword_t value) {
 dword_t *mem = (dword_t *) (base);
 *mem = value;
}

byte_t mmio_inb(dword_t base) {
 byte_t *mem = (byte_t *) (base);
 return *mem;
}

word_t mmio_inw(dword_t base) {
 word_t *mem = (word_t *) (base);
 return *mem;
}
