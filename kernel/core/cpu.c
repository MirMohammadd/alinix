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
MODULE_VERSION("1.0")


/*Parameters should be pointer type*/
/**
 * @brief Executes the CPUID instruction.
 *
 * This function executes the CPUID instruction with the given register value and retrieves the values of the EAX, EBX, ECX, and EDX registers.
 *
 * @warning This function is static and should not be declared in any header files. It is only meant to be used internally within this source file.
 *
 * @param reg The register value to pass to the CPUID instruction.
 * @param eax A pointer to store the value of the EAX register.
 * @param ebx A pointer to store the value of the EBX register.
 * @param ecx A pointer to store the value of the ECX register.
 * @param edx A pointer to store the value of the EDX register.
 */
static inline void cpuid(uint32_t reg, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx){
    /**
     * @warning Do not set this function in any header files, this function is STATIC!!!
    */
    asm volatile("cpuid"
    : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
    : "0" (reg));
}
/**
 * @brief Prints the CPU vendor information.
 *
 * This function retrieves the CPU vendor information by executing the CPUID instruction with the register value of 0, and prints the vendor information to the console.
 */
void PrintCpuVendor(){
    uint32_t LargeStdFunc;
    char vendor[13];
    cpuid(0,&LargeStdFunc,(uint32_t*)(vendor + 0), (uint32_t *)(vendor + 8), (uint32_t *)(vendor + 4));
    Write("CPU Vendor:");
    Write(vendor);
}
/**
 * @brief Enables the CPU features that are necessary for the system to function properly.
 *
 * This function checks the CPU features by executing the CPUID instruction with the register value of 0x01, and enables the necessary features for the system to function properly.
 * If the CPU does not have the required features, the function prints an error message and enters an infinite loop.
 */
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