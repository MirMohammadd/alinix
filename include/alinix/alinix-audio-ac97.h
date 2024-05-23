#ifndef __AUDIO_C_97_H
#define __AUDIO_C_97_H


#define AC97_VENDOR_ID_REGISTER 0x00
#define AC97_RESET_REGISTER 0x00
#define AC97_MASTER_VOLUME_REGISTER 0x02
#define AC97_PCM_OUT_VOLUME_REGISTER 0x18


#include <alinix/port.h>
#include <alinix/types.h>

struct ac97_codec{
    uint32_t base_address;
    uint32_t irq;
    bool initialized;
} ac97_codec_t;




#endif