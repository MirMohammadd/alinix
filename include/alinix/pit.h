#ifndef __ALINIX_KERNEL_PIT_HEADER_H
#define __ALINIX_KERNEL_PIT_HEADER_H


#define PIT_FREQUENCY 1000


#include <alinix/types.h>

typedef struct {
    volatile uint64_t timer_ticks;
} PIT;

PIT* pit;
PIT* PIT_init();
uint32_t PIT_HandleInterrupt(PIT* pit, uint32_t esp);
void PIT_Sleep(PIT* pit, uint32_t ms);
void PIT_PlaySound(PIT* pit, uint32_t nFrequence);
void PIT_NoSound(PIT* pit);
void PIT_Beep(PIT* pit);
void PIT_Beep_freq(PIT* pit, uint32_t freq);
void PIT_Beep_freq_duration(PIT* pit, uint32_t freq, uint32_t duration);
uint64_t PIT_Ticks(PIT* pit);

#endif