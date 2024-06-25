/**
 * @author Ali Mirmohammad
 * @file fadt.c
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

/**
 * @abstraction:
 *  - default handler for the ACPI kernel.
*/


#include <alinix/fadt.h>
#include <alinix/string.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("FADT")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")

struct ACPISDTHeader *h;


/**
 * @brief Checks the sum of the table headers
*/
bool fadtChecksum(struct ACPISDTHeader *tableHeader){
    unsigned char sum = 0;

    for (int i = 0; i < tableHeader->Length;i++){
        sum += ((char *)tableHeader)[i];
    }
    return sum == 0;
}

/**
 * Finds the FACP (Fixed ACPI Description Table) in the System Descriptor Table (SDT) hierarchy.
 *
 * @param RootSDT A pointer to the root System Descriptor Table.
 *
 * @return A pointer to the FACP structure, or NULL if not found.
 *
 * @throws None.
 *
 * @details
 * This function searches for the FACP (Fixed ACPI Description Table) in the System Descriptor Table
 * (SDT) hierarchy starting from the given root SDT. It assumes that the `struct RSDT` and `struct SDTH`
 * structures are defined elsewhere in the codebase.
 *
 * The function casts the `RootSDT` parameter to a pointer to a `struct RSDT` and calculates the number
 * of entries in the RSDT by dividing the length of the RSDT structure by the size of a single entry.
 *
 * The function then iterates through the entries in the RSDT, retrieves each entry's header, and checks
 * if the signature of the header matches the signature of the FACP. If a match is found, the function
 * returns a pointer to the FACP structure.
 *
 * If the iteration reaches the end of the RSDT without finding a match, the function returns NULL.
 *
 * @note
 * This function assumes that the `struct RSDT` and `struct SDTH` structures are defined correctly and
 * that the `strcmp` function is available for string comparison. It also assumes that the "FACP" string
 * is defined as a constant elsewhere in the codebase.
 */
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