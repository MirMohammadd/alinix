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
 *  - default handler for the ACPI kernel.
*/

#include <alinix/ucapi/types.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("UCAPI types")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

const char *uacpi_address_space_to_string(
    enum uacpi_address_space space
)
{
    switch (space) {
    case UACPI_ADDRESS_SPACE_SYSTEM_MEMORY:
        return "SystemMemory";
    case UACPI_ADDRESS_SPACE_SYSTEM_IO:
        return "SystemIO";
    case UACPI_ADDRESS_SPACE_PCI_CONFIG:
        return "PCI_Config";
    case UACPI_ADDRESS_SPACE_EMBEDDED_CONTROLLER:
        return "EmbeddedControl";
    case UACPI_ADDRESS_SPACE_SMBUS:
        return "SMBus";
    case UACPI_ADDRESS_SPACE_SYSTEM_CMOS:
        return "SystemCMOS";
    case UACPI_ADDRESS_SPACE_PCI_BAR_TARGET:
        return "PciBarTarget";
    case UACPI_ADDRESS_SPACE_IPMI:
        return "IPMI";
    case UACPI_ADDRESS_SPACE_GENERAL_PURPOSE_IO:
        return "GeneralPurposeIO";
    case UACPI_ADDRESS_SPACE_GENERIC_SERIAL_BUS:
        return "GenericSerialBus";
    case UACPI_ADDRESS_SPACE_PCC:
        return "PCC";
    case UACPI_ADDRESS_SPACE_PRM:
        return "PRM";
    case UACPI_ADDRESS_SPACE_FFIXEDHW:
        return "FFixedHW";
    case UACPI_ADDRESS_SPACE_TABLE_DATA:
        return "TableData";
    default:
        return "<vendor specific>";
    }
}