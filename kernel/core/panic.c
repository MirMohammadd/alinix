/**
 * @author Ali Mirmohammad
 * @file panic.c
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

#include <alinix/panic.h>
#include <alinix/log.h>
#include <alinix/idt.h>
#include <alinix/enums.h>

void Panic(){
    Log(Error, "-------------------------------");
    Log(Error, "--------- Kernel Halted -------");
    Log(Error, "-------------------------------");

    DisableInterrupts();
    while(1) {
        asm("hlt");
    }
}
