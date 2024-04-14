#include <hal/hal.h>

void pic_send_command(uint8_t cmd, uint8_t pic) {
    if(pic == 0)
        outportb(PIC1_REG_COMMAND, cmd);
    else if(pic == 1)
        outportb(PIC2_REG_COMMAND, cmd);
}

void pic_send_data(uint8_t data, uint8_t pic) {
    if(pic == 0)
        outportb(PIC1_REG_DATA, data);
    else if(pic == 1)
        outportb(PIC2_REG_DATA, data);
}

uint8_t pic_read_data(uint8_t pic) {
    if(pic == 0)
        return inportb(PIC1_REG_DATA);
    else if(pic == 1)
        return inportb(PIC2_REG_DATA);
    else
        return NULL;
}

void pic_init(uint8_t base0, uint8_t base1) {
    uint8_t icw = 0;
    
    disable_int();
    
    icw = (icw & ~PIC_INIT_MASK) | PIC_INIT_YES;
    icw = (icw & ~PIC_IC4_MASK) | PIC_IC4_EXPECT;
    
    pic_send_command(icw, 0);
    pic_send_command(icw, 1);
    
    pic_send_data(base0, 0);
    pic_send_data(base1, 1);
    
    pic_send_data(0x04, 0);
    pic_send_data(0x02, 1);
    
    icw = (icw & ~PIC_UPM_MASK) | PIC_UPM_86MODE;
    
    pic_send_data(icw, 0);
    pic_send_data(icw, 1);
}
