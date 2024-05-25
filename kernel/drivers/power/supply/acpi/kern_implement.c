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

#include <alinix/ucapi/api.h>
#include <alinix/ucapi/types.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("UCAPI")
MODULE_LICENSE("AGPL-3.0")



uacpi_status uacpi_kernel_raw_io_write(
    u64, u8, u64
){
    return UACPI_STATUS_OK;
}

uacpi_status uacpi_kernel_raw_io_read(
    u64, u8, u64 *ret
){
    *ret = 0xFFFFFFFFFFFFFFFF;
    return UACPI_STATUS_OK;
}


void uacpi_kernel_log(enum uacpi_log_level lvl, const char* text, ...)
{
    va_list vlist;
    va_start(vlist, text);

    uacpi_kernel_vlog(lvl, text, vlist);

    va_end(vlist);
}

void uacpi_kernel_vlog(enum uacpi_log_level lvl, const char* text, va_list vlist)
{
    const char *lvl_str;

    switch (lvl) {
    case UACPI_LOG_DEBUG:
        lvl_str = "DEBUG";
        break;
    case UACPI_LOG_TRACE:
        lvl_str = "TRACE";
        break;
    case UACPI_LOG_INFO:
        lvl_str = "INFO";
        break;
    case UACPI_LOG_WARN:
        lvl_str = "WARN";
        break;
    case UACPI_LOG_ERROR:
        lvl_str = "ERROR";
        break;
    default:
        ;
    }

}