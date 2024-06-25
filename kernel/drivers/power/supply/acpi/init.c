/**
 * @author Ali Mirmohammad
 * @file init.c
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
 * 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @abstraction:
 *  - ACPI driver
*/

#include <alinix/init_power.h>
#include <alinix/port.h>
#include <alinix/init.h>
#include <alinix/kernel.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Initialize power management")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

struct FADT *fadt;

/**
 * @ref https://wiki.osdev.org/Acpi
*/

static inline void settle_io_ports(){
    outportb(fadt->SMI_CommandPort,fadt->AcpiEnable);
}


/**
 * @brief Initializes the power management by waiting until the PM1aControlBlock register is set to 1.
 *
 * This function waits in an infinite loop until the `PM1aControlBlock` register is set to 1. The `PM1aControlBlock` register is read using the `inportw()` function, which reads a 16-bit word from the specified port. The `& 1 == 0` condition checks if the least significant bit of the read value is 0, indicating that the `PM1aControlBlock` register is not set to 1.
 *
 * @return This function does not return a value.
 *
 * @note This function assumes that the `fadt` pointer is pointing to a valid `FADT` structure.
 */
VOID init_port_power(){
    while (inportw(fadt->PM1aControlBlock) & 1 == 0);
}