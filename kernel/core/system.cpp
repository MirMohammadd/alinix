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

/**
 * @abstraction:
 *  - Kernel system driver , core implemented for C++.
*/
#include <alinix/system.hpp>
#include <alinix/stream.hpp>
#include <alinix/system.h>
#include <alinix/components/graphicdevice.hpp>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel system driver")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")



GraphicsDevice* System::gfxDevice = 0;
SharedSystemInfo* System::systemInfo = 0;