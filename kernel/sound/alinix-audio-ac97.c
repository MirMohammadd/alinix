#include <alinix/alinix-audio-ac97.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>

struct ac97_codec* ac97Dev;

static inline void ac97_write_register(uint16_t reg,uint16_t value){
    outportw(ac97Dev->base_address + reg,value);
}