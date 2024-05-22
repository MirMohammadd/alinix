#include <alinix/drivers/audio/als4000/als4000.h>
#include <alinix/drivers/audio/als4000/sound.h>
#include <alinix/drivers/audio/als4000/mixer.h>


#include <alinix/module.h>
#include <alinix/kernel.h>
#include <alinix/init.h>

uint32_t dev_mixer_read(uint32_t *base, uint32_t reg){
    uint32_t res;
    res = inportl(base[0] + REG_SB_BASE); // Use inportl instead of outportb
    return res;
}

void dev_mixer_write(uint32_t *base, uint32_t reg, uint32_t val){
    uint32_t res;
    res = inportl(base[0] + REG_SB_BASE); // Use inportl instead of outportb
}
