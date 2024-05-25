/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/
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
        case Cd:
            cmdLeft = MASTER_VOLUME_LCH;
            cmdRight = MASTER_VOLUME_RCH;
            break;
        case Line:
            cmdLeft = MASTER_VOLUME_LCH;
            cmdRight = MASTER_VOLUME_RCH;
            break;
        case Mic:
            cmdLeft = cmdRight = MONO_OUT_VOLUME;
            break;
        case Treble:
            return 22;
		case Bass:
			return 22;
		default:
			return 22;
    } if (flag){
        if (level->right < 0)
            level->right = 0;
        else if (level->right > max_level)
            level->right = max_level;
        if (level->left < 0)
            level->left = 0;
        else if (level->left > max_level)
            level->left = max_level;
        
        dev_mixer_write(base,cmdLeft,0x1f - level->left);
        dev_mixer_write(base,cmdRight,0x1f - level->right);
        mixer_value[cmdLeft] = 0x1f - level->left;
        mixer_value[cmdRight] = 0x1f - level->right;
    }else {
        dev_mixer_read(base,cmdLeft);
        dev_mixer_read(base,cmdRight);
        level->left = 0x1f - mixer_value[cmdLeft];
        level->right = 0x1f - mixer_value[cmdRight];
    }
    return 0;
}