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