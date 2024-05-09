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
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/ucapi/types.h>

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