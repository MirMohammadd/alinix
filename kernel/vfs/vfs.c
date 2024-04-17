#include <alinix/vfs/virtualfilesystem.h>

VirtualFileSystem* VirtualFileSystem_create(Disk* disk, uint32_t start, uint32_t size, char* name) {
    VirtualFileSystem* vfs = (VirtualFileSystem*)malloc(sizeof(VirtualFileSystem));
    vfs->disk = disk;
    vfs->StartLBA = start;
    vfs->SizeInSectors = size;
    if (name != NULL) {
        vfs->Name = name;
    } else {
        vfs->Name = "Unkown";
    }
    return vfs;
}