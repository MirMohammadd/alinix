/**
 * @author Ali Mirmohammad
 * @file apm.c
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
 *  - Utility for APM and components of the kernel.
*/
#include <alinix/apm.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("APM and kernel components")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")



char* GetComponentName(SystemComponent* component) {
    return component->Name;
}

char* GetComponentDescription(SystemComponent* component) {
    return component->Description;
}


APMController* APMController_create();