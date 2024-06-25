/**
 * @author Ali Mirmohammad
 * @file interpreter.c
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
 *  - ACPI driver.
*/

#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/ucapi/types.h>
#include <alinix/ucapi/codes.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("A simple kernel module for ACPI")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")


/**
 * @ref https://github.com/UltraOS/uACPI
*/

struct package_length {
    u32 begin;
    u32 end;
};

struct item{
    u8 type;
    union {
        uacpi_handle handle;
        uacpi_object *obj;
        struct uacpi_namespace_node *node;
        struct package_length pkg;
        u64 immediate;
        u8 immediate_bytes[8];
    };
};

enum item_type {
    ITEM_NONE = 0,
    ITEM_NAMESPACE_NODE,
    ITEM_NAMESPACE_NODE_METHOD_LOCAL,
    ITEM_OBJECT,
    ITEM_EMPTY_OBJECT,
    ITEM_PACKAGE_LENGTH,
    ITEM_IMMEDIATE,
};

DYNAMIC_ARRAY_WITH_INLINE_STORAGE(item_array, struct item, 8)

struct op_context {
    u8 pc;
    bool preempted;

    /*
     * == 0 -> none
     * >= 1 -> item[idx - 1]
     */
    u8 tracked_pkg_idx;

    const struct uacpi_op_spec *op;
    struct item_array items;
};