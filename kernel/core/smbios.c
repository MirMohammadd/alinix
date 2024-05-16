/**
 * @author Ali Mirmohammad
 * @file smbios.c
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

/**
 * @abstraction:
 *  - Provides util for BIOS.
*/
#include <alinix/smbios.h>
#include <alinix/types.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>

char* CopyString(char* src){
    int len = strlen(src);
    char* ret = (char*)malloc(sizeof(char)*(len+1));
    ret[len] = '\0';
    return ret;
}