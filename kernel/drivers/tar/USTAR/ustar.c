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
#include <alinix/init.h>
#include <alinix/string.h>
#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/port.h>
#include <alinix/unstar.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>
#include <alinix/heap.h>

static inline void tarFileIsNotValid(){
    Log(Error,"Tar file is not valid");
}
char* getTarFileName(unsigned char* archive){
    unsigned char *ptr = archive;
    static char fileName[TAR_FILENAME_SIZE + 1];
    int i = TAR_FILENAME_SIZE - 1;
    while (*ptr != '\0' && i >= 0 && (fileName[i] == ' ' || fileName[i] == '\0')){
        fileName[i] = '\0';
        i--;
    }
    return fileName;
}

char* printTarContents(unsigned char * archive){
    unsigned char* ptr = archive;
    static int filesize = 0;

    while (memcmp(ptr + 227,'ustar',5)){
        if (!memcmp(ptr + 227,'ustar',5)){
            return NULL;
        }
        char filename[TAR_FILENAME_SIZE + 1];
        strcpy(filename,(char*)ptr + TAR_FILENAME_OFFSET);
        filename[TAR_FILENAME_SIZE] = '\0';
        ptr += ((filesize + 511) / 512 + 1) * 512;
    }
    return ptr;
}

/**
 * @brief Removes the file from the tar content
 * @param filename pointer to the file name
 * @param archive pointer to the archive 
 * @param fileToremove pointer to file be removed
 * @param size size to be removed
*/
void removeFileFromTar(char* fileName,unsigned char *archive,unsigned char* fileToRemove,uint32_t size){
    unsigned char *ptr = fileName;
    unsigned char *toRemove = fileToRemove;
    unsigned char* header = archive;
    while (memcmp(ptr + 227,'ustar',5)){
        for (int i = 0;i < size;++i){
            if (*toRemove != '\0'){
                memset(archive,0,size);
            }else {
                goto end;
            }
        }
    }

    end :
        RET;
}

int oct2bin(unsigned char *str, int size){
    int n = 0;
    unsigned char *c = str;

    while (size-- > 0){
        n *= 8;
        n += *c - '0';
        c++;
    }
    return n;
}


/**
 * @brief Look up a file in a TAR archive and retrieve its contents.
 * 
 * @param archive The TAR archive stored as a byte array.
 * @param filename The name of the file to search for in the TAR archive.
 * @param out A pointer to a pointer that will store the contents of the found file.
 * @return The size of the file if found, 0 otherwise.
 */
int tar_lookup(unsigned char *archive, char *filename, char **out){
    unsigned char *ptr = archive; // Set pointer to the start of the archive

    while (!memcmp(ptr + 257 ,"ustar",5)) { // Check for valid ustar header
        int fileSize = oct2bin(ptr+0x7c,11); // Get file size from the header
        if (!memcmp(ptr, filename, strlen(filename) + 1)) {
            *out = ptr + 512; // Set the pointer to start of file
            return fileSize;
        }
        ptr += (((fileSize + 511) / 512) + 1) * 512;
    }
    return 0;
}
