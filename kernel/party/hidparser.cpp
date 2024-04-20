#include <alinix/usb/hidparser.h>
#include <alinix/types.h>


class HIDParser{
    public:
        const uint8_t *report_desc;
        int report_desc_size;
        int pos;
        uint8_t item;
        uint32_t value;
        struct HID_DATA data; 
        int    offset_table[MAX_REPORT][3];  // Store ID, type & offset of report
        int    report_count;                 // Store Report Count
        int    count;         
};