#include <alinix/types.h>
#include <alinix/graphics/model.h>

void display_set_register(uint16_t address,uint8_t value){
    DISPLAY_REGISTER_SELECT(0);
    DISPLAY_CS(0);

    DISPLAY_REGISTER_SELECT(1);			//Select data

    if(address & 0x0001)
	    {
			DISPLAY_WRITE_DATA(value);
		}
    else
	    {
			DISPLAY_WRITE_DATA(value << 8);
		}
}