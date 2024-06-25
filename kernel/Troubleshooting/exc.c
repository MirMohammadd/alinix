/**
 * @author Ali Mirmohammad
 * @file exc.c
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
 *  - exec for troubleshooting.
*/

#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/panic.h>
#include <alinix/Troubleshooting.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Troubleshooting module")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")


static int nestexc = 0;

/**
 * @brief Handles general protection fault (GPF) exceptions.
 *
 * This function handles general protection fault (GPF) exceptions by performing the following steps:
 * 1. Checks if the `nestexc` variable exceeds the `MAX_NESTED_EXCEPTIONS` value. If it does, calls the `Panic` function.
 * 2. Increments the `nestexc` variable by 1.
 * 3. Decrements the `nestexc` variable by 1.
 * 4. Returns without any further action.
 *
 * @note The function assumes that the `nestexc` variable is a global variable and that the `MAX_NESTED_EXCEPTIONS`
 *       macro is defined with an appropriate value. It also assumes that the `Panic` function is available for handling
 *       the panic situation.
 *
 * @example
 * void gpfExcHandler(void)
 * {
 *     gpfExcHandler();
 * }
 */
void gpfExcHandler(void){
    if (nestexc > MAX_NESTED_EXCEPTIONS) Panic();
    nestexc++;

    nestexc--;
    return;
}