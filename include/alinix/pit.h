/**
 * @author Ali Mirmohammad
 * @file pit.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/
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