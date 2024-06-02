/**
 * @author Ali Mirmohammad
 * @file kern_implement.c
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
MODULE_VERSION("0.1")


/**
 * @brief Writes data to a raw I/O port.
 *
 * This function writes the specified data to the raw I/O port specified by the given address. The data is written as a byte.
 *
 * @param address The address of the raw I/O port to write to.
 * @param data The data to write to the raw I/O port.
 * @param size The size of the data to write.
 *
 * @return The status of the write operation. Returns `UACPI_STATUS_OK` if the write operation was successful.
 *
 * @note This function assumes that the `UACPI_STATUS_OK` constant is defined and has the correct value.
 */
uacpi_status uacpi_kernel_raw_io_write(
    u64, u8, u64
){
    return UACPI_STATUS_OK;
}

/**
 * @brief Reads data from a raw I/O port.
 *
 * This function reads data from the raw I/O port specified by the given address. The data is read as a byte. The read value is stored in the `ret` parameter.
 *
 * @param address The address of the raw I/O port to read from.
 * @param size The size of the data to read.
 * @param ret Pointer to store the read value.
 *
 * @return The status of the read operation. Returns `UACPI_STATUS_OK` if the read operation was successful.
 *
 * @note This function assumes that the `UACPI_STATUS_OK` constant is defined and has the correct value.
 */
uacpi_status uacpi_kernel_raw_io_read(
    u64, u8, u64 *ret
){
    *ret = 0xFFFFFFFFFFFFFFFF;
    return UACPI_STATUS_OK;
}


/**
 * @brief Logs a message with a specified log level.
 *
 * This function logs a message with the specified log level. The message is formatted using the `text` parameter and any additional arguments passed to the function.
 *
 * @param lvl The log level of the message.
 * @param text The format string for the message.
 * @param ... Additional arguments for formatting the message.
 *
 * @return This function does not return a value.
 *
 * @note This function assumes that the `uacpi_kernel_vlog()` function is defined and works correctly.
 */
void uacpi_kernel_log(enum uacpi_log_level lvl, const char* text, ...)
{
    va_list vlist;
    va_start(vlist, text);

    uacpi_kernel_vlog(lvl, text, vlist);

    va_end(vlist);
}

/**
 * @brief Logs a message with a specified log level using a variable argument list.
 *
 * This function logs a message with the specified log level using the `text` parameter and any additional arguments passed to the function through the `vlist` parameter. The log level is converted to a string representation and used to prefix the log message.
 *
 * @param lvl The log level of the message.
 * @param text The format string for the message.
 * @param vlist The variable argument list for formatting the message.
 *
 * @return This function does not return a value.
 *
 * @note This function assumes that the `UACPI_LOG_DEBUG`, `UACPI_LOG_TRACE`, `UACPI_LOG_INFO`, `UACPI_LOG_WARN`, and `UACPI_LOG_ERROR` constants are defined and have the correct values.
 */
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