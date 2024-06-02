/**
 * @author Ali Mirmohammad
 * @file default_handlers.c
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
MODULE_VERSION("0.1")

#define PCI_ROOT_PNP_ID "PNP0A03"
#define PCI_EXPRESS_ROOT_PNP_ID "PNP0A08"


/**
 * Finds the PCI root node in the ACPI namespace starting from the given node.
 *
 * @param node A pointer to the ACPI namespace node to start the search from.
 *
 * @return A pointer to the PCI root node in the ACPI namespace, or NULL if not found.
 *
 * @throws None.
 *
 * @details
 * This function searches for the PCI root node in the ACPI namespace starting from the given node.
 * It assumes that the `uacpi_namespace_node` structure and the `uacpi_namespace_root` function are
 * defined elsewhere in the codebase.
 *
 * The function initializes an array of PCI root IDs, which are used to identify the PCI root node.
 * It then iterates through the parent nodes of the given node until it reaches the root node of the
 * ACPI namespace.
 *
 * During the iteration, the function checks if the parent node's device ID matches any of the PCI
 * root IDs. If a match is found, the function returns a pointer to the parent node.
 *
 * If the iteration reaches the root node without finding a match, the function returns NULL.
 *
 * @note
 * This function assumes that the PCI root IDs are defined as constants elsewhere in the codebase.
 * It also assumes that the `uacpi_namespace_node` structure and the `uacpi_namespace_root` function
 * are defined correctly.
 */
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