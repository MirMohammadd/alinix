/**
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

#ifndef __ALINIX_KERNEL_CPU_H
#define __ALINIX_KERNEL_CPU_H

#include <alinix/types.h>
#include <alinix/device.h>

#define EDX_SSE2 (1 << 26) // Streaming SIMD Extensions 2
#define EDX_FXSR (1 << 24) // Can we use the fxsave/fxrstor instructions?


/*This function will print the CPU vendor*/
void PrintCpuVendor();

/*Initiate the CPU*/
void enableCpuFeatures();


/////////////////////
/// @brief ////////
//////////////////////
// Defining the CPU informations for kernel drivers
struct cpu{
    int node_id;
    int hotpluggable;
    struct device dev;
};


#endif /*__ALINIX_KERNEL_CPU_H*/