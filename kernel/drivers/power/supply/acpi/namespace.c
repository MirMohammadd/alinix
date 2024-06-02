/**
 * @author Ali Mirmohammad
 * @file namespace.c
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
MODULE_DESCRIPTION("UCAPI namespace")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

uacpi_namespace_node
predefined_namespaces[UACPI_PREDEFINED_NAMESPACE_MAX + 1] = {
    [UACPI_PREDEFINED_NAMESPACE_ROOT] = { .name.text = "\\" },
    [UACPI_PREDEFINED_NAMESPACE_GPE] = { .name.text = "_GPE" },
    [UACPI_PREDEFINED_NAMESPACE_PR] = { .name.text = "_PR_" },
    [UACPI_PREDEFINED_NAMESPACE_SB] = { .name.text = "_SB_" },
    [UACPI_PREDEFINED_NAMESPACE_SI] = { .name.text = "_SI_" },
    [UACPI_PREDEFINED_NAMESPACE_TZ] = { .name.text = "_TZ_" },
    [UACPI_PREDEFINED_NAMESPACE_GL] = { .name.text = "_GL_" },
    [UACPI_PREDEFINED_NAMESPACE_OS] = { .name.text = "_OS_" },
    [UACPI_PREDEFINED_NAMESPACE_OSI] = { .name.text = "_OSI" },
    [UACPI_PREDEFINED_NAMESPACE_REV] = { .name.text = "_REV" },
};

/**
 * @brief Returns a pointer to the root namespace node of the ACPI namespace.
 *
 * This function returns a pointer to the root namespace node of the ACPI namespace. The root node represents the top-level node of the namespace hierarchy.
 *
 * @return A pointer to the root namespace node.
 *
 * @note This function assumes that the `predefined_namespaces` array is defined and has the correct size.
 */
uacpi_namespace_node *uacpi_namespace_root(void)
{
    return &predefined_namespaces[UACPI_PREDEFINED_NAMESPACE_ROOT];
}