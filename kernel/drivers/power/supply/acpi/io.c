#include <alinix/init.h>
#include <alinix/ucapi/types.h>
#include <alinix/compiler.h>
#include <alinix/ucapi/acpi.h>
#include <alinix/stdio.h>
#include <alinix/ucapi/io.h>
#include <alinix/ucapi/log.h>





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

