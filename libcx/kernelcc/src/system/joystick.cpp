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
#include <core/port.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/c++/gameport.hpp>
#include <system/log.h>

struct JoystickStatus *jst;

using namespace CactusOS::system;
bool joystick_button_cxx(uint8_t buttonnum){
    int i;
    for (i = 4; i <= 8; ++i){
        if (joystick_values[i] == buttonnum){
            return ((CactusOS::core::inportb(JOYSTICK_PORT) & buttonnum) == 0);
        }
    }
    // Log(Error,"Invalid value:; Out of bounds.\n");
    return 0;
}

struct JoystickStatus joystick_dump(void)
{
    struct JoystickStatus jst;
    jst.AxisX   = joy_stick_status_cxx(JoystickAxisX);
    jst.AxisY   = joy_stick_status_cxx(JoystickAxisY);
    jst.DeltaX  = joy_stick_status_cxx(JoystickDeltaX);
    jst.DeltaY  = joy_stick_status_cxx(JoystickDeltaY);
    jst.ButtonA = joystick_button_cxx(joy_stick_status_cxx(JoystickButtonA));
    jst.ButtonB = joystick_button_cxx(joy_stick_status_cxx(JoystickButtonB));
    jst.ButtonC = joystick_button_cxx(joy_stick_status_cxx(JoystickButtonC));
    jst.ButtonD = joystick_button_cxx(joy_stick_status_cxx(JoystickButtonD));
    return jst;
}
/* 
 * There's no IRQ for joystick port, so we poll instead.
 * However isn't a problem, because very few data is transmitted
 * through game port.
 */

uint16_t joy_stick_status_cxx(uint8_t byte){
    int time_out = 0;
    /* Disable interrupts, so they don't affect timing */
    asm volatile("cli");
    /* Any read needs to be with a write. The byte that we send 
     * can be garbage, it doesn't matters.
     */
    unsigned char stat = (uint16_t)CactusOS::core::inportb(JOYSTICK_PORT);
    CactusOS::core::outportb(JOYSTICK_PORT, GARBAGE_DATA);

    while (1){
        if (stat & byte){
            jst->JoystickFlag = true;
            break;

        }
        else if (time_out == MAX_TIME_ATTEMPTS){
            jst->JoystickFlag = false;
            return 0;
        }
        ++time_out;
    }
    asm volatile("sti");
    return (stat & byte);
}