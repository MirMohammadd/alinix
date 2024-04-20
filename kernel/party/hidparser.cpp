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
        /////////////////////////////////
        uint16_t u_page;
        struct HID_NODE usage_table[USAGE_TAB_SIZE]; // Usage stack
        int    usage_size;                   // Design number of usage used
        int    usage_min;
        int    usage_max;    
        int    cnt_object;                   // Count objects in Report Descriptor
        int    cnt_report;  
        public:
            bool Parse(struct HID_DATA* data);
            void Reset();
            bool FindObject(struct HID_DATA* data);
            int* GetReportOffset(const uint8_t report_id, const uint8_t report_type);        
};

extern "C" HIDParser* HIDParser_Parse(struct HID_DATA* data){
    return reinterpret_cast<HIDParser*>(new HIDParser());
}