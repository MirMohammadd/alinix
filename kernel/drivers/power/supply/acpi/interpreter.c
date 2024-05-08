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