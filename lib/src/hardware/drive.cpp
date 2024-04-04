#include <hardware/ata.hpp>
#include <types.h>

using namespace LIBHeisenKernel;

double getDriveSize(int drive)
{
    uint64_t size = (double)ata_identify_drive(drive);
    double mega_bytes = size/1024* 1024;
    return mega_bytes;
}

