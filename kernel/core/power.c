/**
 * @author Ali Mirmohammad
 * @file power.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Provides utility over the power management of the kernel.
*/
#include <alinix/power.h>
#include <alinix/core/power.h>
#include <alinix/types.h>
#include <alinix/enums.h>
#include <alinix/log.h>
#include <alinix/memory.h>
#include <alinix/types.h>
#include <alinix/apm.h>
#include <alinix/pit.h>
#include <alinix/port.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Power Management")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


uint32_t* SMI_CMD;
uint8_t ACPI_ENABLE;
uint8_t ACPI_DISABLE;
uint32_t* PM1a_CNT;
uint32_t* PM1b_CNT;
uint16_t SLP_TYPa;
uint16_t SLP_TYPb;
uint16_t SLP_EN;
uint16_t SCI_EN;
uint8_t PM1_CNT_LEN;


/**
 * @brief Checks for a valid ACPI Root System Description Pointer (RSDP).
 *
 * This function verifies if the memory pointed to by `ptr` contains a valid RSDP by checking its
 * signature and checksum. If valid, it returns the address of the Root System Description Table (RSDT).
 *
 * @param ptr A pointer to the memory location that potentially contains the RSDP.
 * @return A pointer to the RSDT if the RSDP is valid; returns 0 if the RSDP is not valid.
 */
unsigned int* acpiCheckRSDPtr(unsigned int* ptr)
{
    char* sig = "RSD PTR ";
    struct RSDPtr* rsdp = (struct RSDPtr*)ptr;
    uint8_t* bptr;
    uint8_t check = 0;
    int i;

    if(memcmp(sig, rsdp, 8) == 0)
    {
        // check checksum rsdpd
        bptr = (uint8_t*)ptr;
        for (i = 0; i < (int)sizeof(struct RSDPtr); i++)
        {
            check += *bptr;
            bptr++;
        }

        // found valid rsdpd   
        if (check == 0) {
            if (rsdp->Revision == 0)
                Log(Info, "ACPI Version 1");
            else
                Log(Info, "ACPI Version 2");
            
            return (unsigned int*)rsdp->RsdtAddress;
        }
    }

    return 0;
}



// finds the acpi header and returns the address of the rsdt

/**
 * @brief Searches for the Root System Description Pointer (RSDP) in memory.
 *
 * This function searches for the RSDP in the memory range below 1MB and in the Extended BIOS Data Area (EBDA).
 * If a valid RSDP is found, it returns its address.
 *
 * @return A pointer to the RSDP if found; returns 0 if no valid RSDP is found.
 */
unsigned int* acpiGetRSDPtr(void)
{
    unsigned int* addr;
    unsigned int* rsdp;

    // search below the 1mb mark for RSDP signature
    for(addr = (unsigned int*)0x000E0000; (int)addr < 0x00100000; addr += 0x10/sizeof(addr))
    {
        rsdp = acpiCheckRSDPtr(addr);
        if (rsdp != 0)
            return rsdp;
    }

    // at address 0x40:0x0E is the RM segment of the ebda
    int ebda = *((short*)0x40E);   // get pointer
    ebda = ebda*0x10 & 0x000FFFFF;   // transform segment into linear address

    // search Extended BIOS Data Area for the Root System Description Pointer signature
    for(addr = (unsigned int*)ebda; (int)addr < ebda + 1024; addr += 0x10/sizeof(addr))
    {
        rsdp = acpiCheckRSDPtr(addr);
        if (rsdp != 0)
            return rsdp;
    }

    return 0;
}



/**
 * @brief Checks for a valid ACPI header by verifying the signature and checksum.
 *
 * This function checks if the memory pointed to by `ptr` contains a valid ACPI table header
 * by comparing the signature and verifying the checksum.
 *
 * @param ptr A pointer to the memory location that potentially contains the ACPI table header.
 * @param sig A string representing the expected signature of the ACPI table header.
 * @return 0 if the header is valid (signature matches and checksum is correct); returns -1 if the header is not valid.
 */
// checks for a given header and validates checksum
int acpiCheckHeader(unsigned int* ptr, char* sig)
{
    if(memcmp(ptr, sig, 4) == 0)
    {
        char* checkPtr = (char*)ptr;
        int len = *(ptr + 1);
        char check = 0;
        while (0 < len--)
        {
            check += *checkPtr;
            checkPtr++;
        }
        if (check == 0)
            return 0;
    }
    return -1;
}

/**
 * @brief Enables ACPI (Advanced Configuration and Power Interface) if it is not already enabled.
 *
 * This function checks if ACPI is enabled. If not, it attempts to enable ACPI by sending the appropriate command.
 * It waits for up to 3 seconds to ensure ACPI is enabled. It logs the result of the operation.
 *
 * @return 0 if ACPI is successfully enabled or already enabled; returns -1 if ACPI could not be enabled.
 */
int acpiEnable(void)
{
    // check if acpi is enabled
    if ((inportw((unsigned int) PM1a_CNT) & SCI_EN) == 0 )
    {
        // check if acpi can be enabled
        if (SMI_CMD != 0 && ACPI_ENABLE != 0)
        {
            outportb((unsigned int)SMI_CMD, ACPI_ENABLE); // send acpi enable command
            // give 3 seconds time to enable acpi
            int i;
            for (i = 0; i < 300; i++)
            {
                if ((inportw((unsigned int)PM1a_CNT) & SCI_EN) == 1)
                    break;
                
                
            }
            if (PM1b_CNT != 0)
                for (; i < 300; i++ )
                {
                    if ((inportw((unsigned int) PM1b_CNT) & SCI_EN) == 1)
                        break;
                    
                    
                }
            if (i < 300) {
                Log(Info, "Enabled ACPI");
                return 0;
            } else {
                Log(Info, "Couldn't Enable ACPI");
                return -1;
            }
        } else {
            Log(Info, "No known way to Enable ACPI");
            return -1;
        }
    } else {
        Log(Info, "ACPI was already enabled");
        return 0;
    }
}



//
// bytecode of the \_S5 object
// -----------------------------------------
//        | (optional) |    |    |    |   
// NameOP | \          | _  | S  | 5  | _
// 08     | 5A         | 5F | 53 | 35 | 5F
//
// -----------------------------------------------------------------------------------------------------------
//           |           |              | ( SLP_TYPa   ) | ( SLP_TYPb   ) | ( Reserved   ) | (Reserved    )
// PackageOP | PkgLength | NumElements  | byteprefix Num | byteprefix Num | byteprefix Num | byteprefix Num
// 12        | 0A        | 04           | 0A         05  | 0A          05 | 0A         05  | 0A         05
//
//----this-structure-was-also-seen----------------------
// PackageOP | PkgLength | NumElements |
// 12        | 06        | 04          | 00 00 00 00
//
// (Pkglength bit 6-7 encode additional PkgLength bytes [shouldn't be the case here])
//
/**
 * Initialize the ACPI subsystem.
 *
 * This function initializes the ACPI subsystem by searching for the ACPI tables and parsing the FACP table.
 * It performs the following steps:
 *
 * 1. Get the address of the RSDT (Root System Description Table) using the `acpiGetRSDPtr` function.
 * 2. Check if the address is valid (if ACPI is available on this PC) by checking the ACPI header.
 * 3. If the address is valid, iterate over the RSDT entries to find the FACP (Fixed ACPI Description Table).
 * 4. Parse the FACP table to extract the necessary information for ACPI initialization.
 * 5. Search for the \_S5 package in the DSDT (Differentiated System Description Table).
 * 6. Check if the \_S5 package is valid and extract the required values.
 * 7. Initialize the ACPI subsystem with the extracted values.
 * 8. Return 0 if the initialization is successful.
 *
 * @return 0 if the ACPI subsystem is successfully initialized, -1 otherwise.
 *
 * @throws None.
 */
int initAcpi(void)
{
    unsigned int* ptr = acpiGetRSDPtr();

    // check if address is correct  ( if acpi is available on this pc )
    if (ptr != 0 && acpiCheckHeader(ptr, "RSDT") == 0)
    {
        // the RSDT contains an unknown number of pointers to acpi tables
        int entrys = *(ptr + 1);
        entrys = (entrys-36) / 4;
        ptr += 36/4;   // skip header information

        while (0<entrys--)
        {
            // check if the desired table is reached
            if (acpiCheckHeader((unsigned int*)*ptr, "FACP") == 0)
            {
                entrys = -2;
                struct FACP* facp = (struct FACP*)*ptr;
                
                if (acpiCheckHeader((unsigned int*)facp->DSDT, "DSDT") == 0)
                {
                    // search the \_S5 package in the DSDT
                    char *S5Addr = (char*)facp->DSDT + 36; // skip header
                    int dsdtLength = *(facp->DSDT+1) - 36;
                    while (0 < dsdtLength--)
                    {
                        if (memcmp(S5Addr, "_S5_", 4) == 0)
                            break;
                        S5Addr++;
                    }
                    // check if \_S5 was found
                    if (dsdtLength > 0)
                    {
                        // check for valid AML structure
                        if ((*(S5Addr-1) == 0x08 || (*(S5Addr - 2) == 0x08 && *(S5Addr-1) == '\\') ) && *(S5Addr+4) == 0x12 )
                        {
                            S5Addr += 5;
                            S5Addr += ((*S5Addr &0xC0) >> 6) + 2;   // calculate PkgLength size

                            if (*S5Addr == 0x0A)
                                S5Addr++;   // skip byteprefix
                            SLP_TYPa = *(S5Addr) << 10;
                            S5Addr++;

                            if (*S5Addr == 0x0A)
                                S5Addr++;   // skip byteprefix
                            SLP_TYPb = *(S5Addr) << 10;

                            SMI_CMD = facp->SMI_CMD;

                            ACPI_ENABLE = facp->ACPI_ENABLE;
                            ACPI_DISABLE = facp->ACPI_DISABLE;

                            PM1a_CNT = facp->PM1a_CNT_BLK;
                            PM1b_CNT = facp->PM1b_CNT_BLK;
                            
                            PM1_CNT_LEN = facp->PM1_CNT_LEN;

                            SLP_EN = 1 << 13;
                            SCI_EN = 1;

                            return 0;
                        } else {
                            Log(Info, "\\_S5 parse error");
                        }
                    } else {
                        Log(Info, "\\_S5 not present");
                    }
                } else {
                    Log(Info, "DSDT invalid");
                }
            }
            ptr++;
        }
        Log(Info, "no valid FACP present");
    } else {
        Log(Info, "no ACPI");
    }

    return -1;
}
/**
 * Initializes the system by enabling page fault auto-fix, initializing ACPI, and disabling page fault auto-fix.
 *
 * This function performs the following steps:
 *
 * 1. Enables page fault auto-fix to allow accessing physical ACPI memory.
 * 2. Initializes the ACPI subsystem using the `initAcpi` function.
 * 3. Disables page fault auto-fix to restore the original behavior.
 *
 * @return None.
 *
 * @throws None.
 */
void Initialize()
{
    //TODO: Find a better way to access physical ACPI memory
    EnablePagefaultAutoFix();
    initAcpi();
    DisablePagefaultAutoFix();
}

/**
 * Powers off the system using ACPI.
 *
 * This function performs the following steps:
 *
 * 1. Check if ACPI shutdown is possible by checking the value of the SCI_EN variable.
 * 2. If ACPI shutdown is not possible, log an error message and return.
 * 3. Enable ACPI using the `acpiEnable` function.
 * 4. Log a message indicating that the system is sending a shutdown command to ACPI.
 * 5. Send the shutdown command to ACPI by writing to the PM1a_CNT and PM1b_CNT registers.
 * 6. If ACPI shutdown fails, log an error message and initiate a reboot.
 *
 * @return None.
 *
 * @throws None.
 */
void Poweroff()
{
    // if(apm->Enabled) {
    //     Log(Info, "Shutdown via APM");
    //     apm->SetPowerState(APM_ALL_DEVICE, APM_POWER_OFF);
    // }
    
    // Else try ACPI

    // SCI_EN is set to 1 if acpi shutdown is possible
    if (SCI_EN == 0)
    {
        Log(Error, "ACPI poweroff not possible");
        return;
    }

    acpiEnable();

    Log(Info, "Sending Shutdown to ACPI");

    // send the shutdown command
    outportw((unsigned int)PM1a_CNT, SLP_TYPa | SLP_EN );
    if (PM1b_CNT != 0)
        outportw((unsigned int)PM1b_CNT, SLP_TYPb | SLP_EN );

    Log(Error, "ACPI poweroff failed, rebooting instead");
    for(int i = 5; i >= 0; i--)
    {
        Log(Info, "%d", i);
        // pit->Sleep(1000);
    }
    Reboot();
}

/**
 * Reboots the system by disabling interrupts and performing a system reset.
 *
 * This function performs the following steps:
 *
 * 1. Disables interrupts to prevent any interruptions during the reboot process.
 * 2. Flushes the keyboard controller by repeatedly checking if there is data available in the keyboard buffer.
 * 3. Sends a reset command to the system by writing 0xFE to the keyboard controller's command port.
 *
 * @return None.
 *
 * @throws None.
 */
void Reboot()
{
    DisableInterrupts();

    /* flush the keyboard controller */
    unsigned temp;
    do
    {
        temp = inportb(0x64);
        if((temp & 0x01) != 0)
        {
            inportb(0x60);
            continue;
        }
    } while((temp & 0x02) != 0);

    /* Reset! */
    outportb(0x64, 0xFE);
}