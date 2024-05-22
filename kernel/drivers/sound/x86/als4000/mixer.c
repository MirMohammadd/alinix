#include <alinix/drivers/audio/als4000/als4000.h>
#include <alinix/drivers/audio/als4000/sound.h>
#include <alinix/drivers/audio/als4000/mixer.h>



uint8_t mixer_value[] = {
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08,
	0x7e, 0x3d, 0x01, 0x01, 0x00, 0x00, 0x03, 0x00,
	0x00, 0x01
};

int get_set_volume(uint8_t *base,struct volume_level *level,int flag){
    int max_level,cmdLeft,cmdRight;
    max_level = 0x1f;
    switch (level->device){
        case Master:
            cmdLeft = MASTER_VOLUME_LCH;
            cmdRight = MASTER_VOLUME_RCH;
            break;
        case Dac:
            return EINIVAL;
        case Fm:
            cmdLeft = MASTER_VOLUME_LCH;
            cmdRight = MASTER_VOLUME_RCH;
            break;
    }
}