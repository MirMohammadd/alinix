#include <alinix/init.h>
#include <alinix/ucapi/types.h>
#include <alinix/compiler.h>
#include <alinix/ucapi/acpi.h>



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

}

uacpi_status uacpi_gas_read(const struct acpi_gas *gas, u64 *out_value){
    uacpi_status ret;
    u8 access_bit_width, access_byte_width;
    u8 bit_offset, bits_left, index = 0;
    u64 data, mask = 0xFFFFFFFFFFFFFFFF;

}