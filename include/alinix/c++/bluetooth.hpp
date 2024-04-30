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
#ifndef __ALINIX_KERNEL_C_PLUS_PLUS_BLUETOOTH_HPP
#define __ALINIX_KERNEL_C_PLUS_PLUS_BLUETOOTH_HPP


#include <alinix/types.h>
#include <alinix/list.h>
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus



class Bluetooth{
    public:
        struct list_head    list;
        uint8_t status;
        uint16_t devices;
        uint16_t services;
        uint16_t characteristics;

        uint8_t* uuid;

        Bluetooth();
        ~Bluetooth();
        virtual void Setup();
        virtual bool GetDeviceList();
        virtual bool GetServiceList();
        virtual bool GetCharacteristics();
};
#ifdef __cplusplus
}
#endif // __cplusplus



#endif // __ALINIX_KERNEL_C_PLUS_PLUS_BLUETOOTH_HPP