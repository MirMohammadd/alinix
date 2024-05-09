#include <alinix/fadt.h>

bool fadtChecksum(struct ACPISDTHeader *tableHeader){
    unsigned char sum = 0;

    for (int i = 0; i < tableHeader->Length;i++){
        sum += ((char *)tableHeader)[i];
    }
    return sum == 0;
}