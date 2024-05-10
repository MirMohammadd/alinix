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

#include <alinix/vfs/vfsmanager.h>
#include <alinix/vfs/virtualfilesystem.h>
#include <alinix/system/component.h>
#include <alinix/system.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>
#include <alinix/string.h>
#include <alinix/ulib.h>
#include <alinix/heap.h>
#include <alinix/convert.h>

int ExtractDiskNumber(const char* path, uint8_t* idSizeReturn){
    if (Contains(path,":") && Contains(path, PATH_SEPERATOR_C)){
        int idLength  = IndexOf(path,':',0);
        char* idStr = (char *)malloc(sizeof(char[idLength]));
        memcpy(idStr,path,idLength);

        int idValue = 0;
        if(isalpha(idStr[0])) //Are we using a character instead of a integer
        {
            switch (idStr[0])
            {
                case 'b':
                case 'B': //Boot partition
                    idValue = bootPartitionID;
                    break;      
                default:
                    free(idStr);
                    return -1;
                    break;
            }
        }
        else
            idValue = StringToInt(idStr);

        free(idStr);

        if(idSizeReturn != 0)
            *idSizeReturn = idLength;   
           
        return idValue;  
    }
    return -1;
    }
