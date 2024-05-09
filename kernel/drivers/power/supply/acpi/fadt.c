#include <alinix/fadt.h>
#include <alinix/string.h>

struct ACPISDTHeader *h;

bool fadtChecksum(struct ACPISDTHeader *tableHeader){
    unsigned char sum = 0;

    for (int i = 0; i < tableHeader->Length;i++){
        sum += ((char *)tableHeader)[i];
    }
    return sum == 0;
}
void *findFACP(void *RootSDT){
    struct RSDT *rsdt = (struct RDST *)RootSDT;
    int entries = (rsdt->h.Length - sizeof(rsdt->h)) / 4;

    for (int i = 0; i < entries;i++){
        if (!strcmp(h->Signature, "FACP")){
            return (void*)h;
        }

    }
    return NULL; // Noting found :))

}