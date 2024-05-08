#include <alinix/ucapi/types.h>

const char *uacpi_address_space_to_string(
    enum uacpi_address_space space
)
{
    switch (space) {
    case UACPI_ADDRESS_SPACE_SYSTEM_MEMORY:
        return "SystemMemory";
    case UACPI_ADDRESS_SPACE_SYSTEM_IO:
        return "SystemIO";
    case UACPI_ADDRESS_SPACE_PCI_CONFIG:
        return "PCI_Config";
    case UACPI_ADDRESS_SPACE_EMBEDDED_CONTROLLER:
        return "EmbeddedControl";
    case UACPI_ADDRESS_SPACE_SMBUS:
        return "SMBus";
    case UACPI_ADDRESS_SPACE_SYSTEM_CMOS:
        return "SystemCMOS";
    case UACPI_ADDRESS_SPACE_PCI_BAR_TARGET:
        return "PciBarTarget";
    case UACPI_ADDRESS_SPACE_IPMI:
        return "IPMI";
    case UACPI_ADDRESS_SPACE_GENERAL_PURPOSE_IO:
        return "GeneralPurposeIO";
    case UACPI_ADDRESS_SPACE_GENERIC_SERIAL_BUS:
        return "GenericSerialBus";
    case UACPI_ADDRESS_SPACE_PCC:
        return "PCC";
    case UACPI_ADDRESS_SPACE_PRM:
        return "PRM";
    case UACPI_ADDRESS_SPACE_FFIXEDHW:
        return "FFixedHW";
    case UACPI_ADDRESS_SPACE_TABLE_DATA:
        return "TableData";
    default:
        return "<vendor specific>";
    }
}