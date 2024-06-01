/**
 * @author Ali Mirmohammad
 * @file cpu.c
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
/**
 * @abstraction:
 *  - Provides utility for CPU.
 *  - Including display the cpu vendor. 
*/
#include <alinix/cpu.h>
#include <alinix/types.h>
#include <alinix/bootconsole.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("CPU utility")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")


/*Parameters should be pointer type*/
static inline void cpuid(uint32_t reg, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx){
    /**
     * @warning Do not set this function in any header files, this function is STATIC!!!
    */
    asm volatile("cpuid"
    : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
    : "0" (reg));
}

void PrintCpuVendor(){
    uint32_t LargeStdFunc;
    char vendor[13];
    cpuid(0,&LargeStdFunc,(uint32_t*)(vendor + 0), (uint32_t *)(vendor + 8), (uint32_t *)(vendor + 4));
    Write("CPU Vendor:");
    Write(vendor);
}

void enableCpuFeatures(){
    /**
     * @brief  Check CPU features
    */
    uint32_t eax, ebx, ecx, edx;

    cpuid(0x01, &eax, &ebx, &ecx, &edx);

    if (edx & EDX_SSE2) { 
        WriteLine("CPU Has SSE2");

        EnableSSE();
    }
    else
    {
        WriteLine("Error: CPU has no SSE2. This is needed");

        while(1);
    }

    if(edx & EDX_FXSR) {
        WriteLine("CPU Has FXSR");
    }
    else
    {
        WriteLine("Error: CPU has no FXSR. This is needed");

        while(1);
    }
}