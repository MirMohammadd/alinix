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



#include <hal/device.h>
#include <lib/string.h>
#include <fs/vfs.h>
#include <drivers/video.h>

static device_t *devices[8];


void device_registerO(device_t *dev){
    if (dev->id < 8){
        devices[dev->id] = dev;
        vfs_mount(dev->mount);
    }
}

device_t *get_dev_by_name(char *name) {
    if(name[0] == '/')
        name++;
    for(int i = 0; i < 8; i++) {
        if(strncmp(devices[i]->mount, name, 3) == 0)
            return devices[i];
    }
    return NULL;
}


device_t *get_dev_by_id(int id) {
    for(int i = 0; i < 8; i++) {
        if(devices[i]->id == id)
            return devices[i];
    }
    return NULL;
}


int get_dev_id_by_name(char *name) {
    if(name[0] == '/')
        name++;
    for(int i = 0; i < 8; i++) {
        if(strncmp(devices[i]->mount, name, 3) == 0)
            return devices[i]->id;
    }
    return -1;
}