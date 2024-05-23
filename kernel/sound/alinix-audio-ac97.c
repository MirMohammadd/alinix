#include <alinix/alinix-audio-ac97.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/pci.h>
#include <interrupt.h>


static inline void ac97_write_register(uint16_t reg,uint16_t value,struct ac97_codec* dev){
    outportw(dev->base_address + reg,value);
}

static inline uint16_t ac97_read_register(uint16_t reg,struct ac97_codec* dev){
    return inportw(dev->base_address + reg);
}


void ac97_initialize(){
    struct ac97_codec* ac97Dev;
    ac97_write_register(AC97_RESET_REGISTER, 0,ac97Dev);
    uint16_t vendor_id = ac97_read_register(AC97_VENDOR_ID_REGISTER,ac97Dev);

    if (vendor_id != 0xFFFF){
        ac97Dev->initialized = true;
    }
    else {
        ac97Dev->initialized = false;
    }
        // Set master volume to maximum
    ac97_write_register(AC97_MASTER_VOLUME_REGISTER, 0x0000,ac97Dev);
    ac97_write_register(AC97_PCM_OUT_VOLUME_REGISTER, 0x0000,ac97Dev);
    EnableInterrupts();

}
