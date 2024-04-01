#include <vfs.hpp>

#include <syscall.hpp>
#include <listing.h>

using namespace LIBHeisenKernel;

bool LIBHeisenKernel::FileExists(char* path)
{
    return (bool)DoSyscall(SYSCALL_FILE_EXISTS, (uint32_t)path);
}
uint32_t LIBHeisenKernel::GetFileSize(char* path)
{
    return (uint32_t)DoSyscall(SYSCALL_GET_FILESIZE, (uint32_t)path);
}
int LIBHeisenKernel::ReadFile(char* path, uint8_t* buffer, uint32_t offset, uint32_t len)
{
    return (int)DoSyscall(SYSCALL_READ_FILE, (uint32_t)path, (uint32_t)buffer, offset, len);
}
int LIBHeisenKernel::WriteFile(char* path, uint8_t* buffer, uint32_t len, bool create)
{
    return (int)DoSyscall(SYSCALL_WRITE_FILE, (uint32_t)path, (uint32_t)buffer, len, (uint32_t)create);
}
int LIBHeisenKernel::CreateFile(char* path)
{
    return (int)DoSyscall(SYSCALL_CREATE_FILE, (uint32_t)path);
}
int LIBHeisenKernel::CreateDirectory(char* path)
{
    return (int)DoSyscall(SYSCALL_CREATE_DIRECTORY, (uint32_t)path);
}
bool LIBHeisenKernel::DirectoryExists(char* path)
{
    return (bool)DoSyscall(SYSCALL_DIR_EXISTS, (uint32_t)path);
}
bool LIBHeisenKernel::EjectDisk(char* path)
{
    return (bool)DoSyscall(SYSCALL_EJECT_DISK, (uint32_t)path);
}
List<VFSEntry> LIBHeisenKernel::DirectoryListing(char* path)
{
    List<VFSEntry> result;

    int items = DoSyscall(SYSCALL_BEGIN_LISTING, DIRECTORY_LISTING, (uint32_t)path);
    if(items == -1)
        return result;
    
    for(int i = 0; i < items; i++) {
        VFSEntry entry;
        int strLen = DoSyscall(SYSCALL_LISTING_ENTRY, DIRECTORY_LISTING, (uint32_t)i, (uint32_t)&entry);
        if(strLen == 0)
            return result; // End of items

        result += entry;
    }
    DoSyscall(SYSCALL_END_LISTING, DIRECTORY_LISTING);
    return result;
}