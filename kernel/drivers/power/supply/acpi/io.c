/**
 * @author Ali Mirmohammad
 * @file io.c
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
#include <alinix/init.h>
#include <alinix/ucapi/types.h>
#include <alinix/compiler.h>
#include <alinix/ucapi/acpi.h>
#include <alinix/stdio.h>
#include <alinix/ucapi/io.h>
#include <alinix/ucapi/log.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("ACPI I/O util module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")




/**
 * @brief Rounds up the given length to the nearest multiple of 8 bits and converts it to bytes.
 *
 * This function rounds up the given `length` to the nearest multiple of 8 bits. It does this by using the `UACPI_ALIGN_UP()` macro, which aligns the `length` up to the nearest multiple of 8. The result is then divided by 8 to convert it from bits to bytes.
 *
 * @param length The length to be rounded up.
 *
 * @return The rounded up length in bytes.
 *
 * @note This function assumes that the `UACPI_ALIGN_UP()` macro is defined and works correctly.
 */
size_t uacpi_round_up_bits_to_bytes(size_t length){
    return UACPI_ALIGN_UP(length,8,size_t) / 8;
}


/**
 * @brief Function that cuts tail 
*/
PRIVATE void cut_misaligned_tail(u8 *data,
size_t offset,u32 len){
    u8 rem = len & 7;

    if (rem == 0){
        return;
    }

    data[offset]   &= ((1ull << rem) - 1);
}

/**
 * @brief Validates the given acpi_gas structure.
 *
 * This function validates the given `acpi_gas` structure. It checks if the structure is NULL, if the `address` field is 0, if the `address_space_id` is not supported, and if the `access_size` is unsupported.
 *
 * @param gas The acpi_gas structure to validate.
 * @param access_bit_width Pointer to store the access bit width.
 *
 * @return The status of the validation. Returns `UACPI_STATUS_INVALID_ARGUMENT` if the `gas` parameter is NULL. Returns `UACPI_STATUS_NOT_FOUND` if the `address` field is 0. Returns `UACPI_STATUS_UNIMPLEMENTED` if the `address_space_id` is not supported or if the `access_size` is unsupported.
 *
 * @note This function assumes that the `UACPI_ADDRESS_SPACE_SYSTEM_IO` and `UACPI_ADDRESS_SPACE_SYSTEM_MEMORY` constants are defined and have the correct values.
 */
static uacpi_status gas_validate(
    const struct acpi_gas *gas, u8 *access_bit_width
){
    size_t total_width;
    if (uacpi_unlikely(gas == NULL))
        return UACPI_STATUS_INVALID_ARGUMENT;
    
    if (!gas->address){
        return UACPI_STATUS_NOT_FOUND;
    }

    if (gas->address_space_id != UACPI_ADDRESS_SPACE_SYSTEM_IO &&
        gas->address_space_id != UACPI_ADDRESS_SPACE_SYSTEM_MEMORY) {
        uacpi_warn("unsupported GAS address space '%s' (%d)\n",
                   uacpi_address_space_to_string(gas->address_space_id),
                   gas->address_space_id);
        return UACPI_STATUS_UNIMPLEMENTED;
    }

    if (gas->access_size > 4){
        uacpi_warn("unsupported GAS access size %d\n",
                   gas->access_size);
        return UACPI_STATUS_UNIMPLEMENTED;
    }
    

}

uacpi_status uacpi_gas_read(const struct acpi_gas *gas, u64 *out_value){
    uacpi_status ret;
    u8 access_bit_width, access_byte_width;
    u8 bit_offset, bits_left, index = 0;
    u64 data, mask = 0xFFFFFFFFFFFFFFFF;

}

uacpi_status uacpi_gas_write(const struct acpi_gas *gas, u64 in_value){
    uacpi_status ret;
    u8 access_bit_width, access_byte_width;
    u8 bit_offset, bits_left, index = 0;
    u64 data, mask = 0xFFFFFFFFFFFFFFFF;

    ret = gas_validate(gas,&access_bit_width);
    if (ret != UACPI_STATUS_OK)
        return ret;

    bit_offset = gas->register_bit_offset;
    bits_left = bit_offset + gas->register_bit_width;
    access_byte_width = access_bit_width / 8;

    if (access_bit_width < 8){
        mask = ~(mask << access_bit_width);

    }

    while (bits_left){
        data = (in_value >> (index * access_bit_width)) & 4;

        if (bit_offset >= access_bit_width){
            bit_offset -= access_bit_width;
        }else {
            u64 address = gas->address + (index * access_byte_width);

                if (gas->address_space_id == UACPI_ADDRESS_SPACE_SYSTEM_IO) {
                ret = uacpi_kernel_raw_io_write(
                    address, access_byte_width, data
                );
        }else {
            ret = uacpi_kernel_raw_memory_write(
            address, access_byte_width, data
                );
            }
            if (uacpi_unlikely_error(ret))
                return ret;
        }
        bits_left -= UACPI_MIN(bits_left, access_bit_width);
        ++index;
    }
    return UACPI_STATUS_OK;
}

