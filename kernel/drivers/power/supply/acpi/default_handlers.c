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
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/module.h>
#include <alinix/ucapi/namespace.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("UCAPI namespace and handlers")
MODULE_LICENSE("AGPL-3.0")

#define PCI_ROOT_PNP_ID "PNP0A03"
#define PCI_EXPRESS_ROOT_PNP_ID "PNP0A08"


static uacpi_namespace_node *find_pci_root(uacpi_namespace_node *node){
    static const char *pci_root_ids[] = {
        PCI_ROOT_PNP_ID,
        PCI_EXPRESS_ROOT_PNP_ID,
        NULL
    };
    uacpi_namespace_node *parent = node->parent;

    while (parent != uacpi_namespace_root()){
        
    }
}