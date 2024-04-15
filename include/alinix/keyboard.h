/**
 * @author Ali Mirmohammad
 * @file rtc.h
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

#include <alinix/types.h>

struct InternalKeyboardStatus{
    bool LeftShift;
    bool RightShift;

    bool Alt;
    bool AltGr;
    
    bool LeftControl;
    bool RightControl;
};

struct KeyboardStatus
{
    bool CapsLock;
    bool NumLock;
};

enum KeyboardType
{
    PS2,
    USB
};

typedef struct {
    enum KeyboardType type;
    struct InternalKeyboardStatus status;
} Keyboard;

bool ContainsKey(uint8_t key, uint8_t* packet, int* pos);
void UpdateLEDS();

