/**
 * @author Ali Mirmohammad
 * @file serialport.c
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
 *  - Provides functionality for the serial ports I/O.
*/

#include <alinix/types.h>
#include <alinix/enums.h>
#include <alinix/port.h>
#include <alinix/serialport.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Serial Port I/O")
MODULE_LICENSE("AGPLv3")
MODULE_VERSION("0.1")


bool ConsoleInitialized;

enum COMPort PortAddress = COM1;
/**
 * @brief Start the kernel serial port with this function.
*/
void Init(enum COMPort port)
{
    PortAddress = port;

    outportb(PortAddress + 1, 0x00);    // Disable all interrupts
    outportb(PortAddress + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outportb(PortAddress + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outportb(PortAddress + 1, 0x00);    //                  (hi byte)
    outportb(PortAddress + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(PortAddress + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(PortAddress + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    ConsoleInitialized = true;
}

/**
 * @brief Checks if the serial port is ready to send data.
 *
 * This function reads the Line Status Register (LSR) of the serial port and checks if the Transmit Holding Register (THR) is empty.
 * It determines if the serial port is ready to send data.
 *
 * @return A non-zero value if the serial port is ready to send data; returns 0 if it is not ready.
 */
int SerialSendReady()
{
    return inportb(PortAddress + 5) & 0x20;
}

/**
 * @brief Writes a null-terminated string to the serial port.
 *
 * This function sends each character of the given null-terminated string to the serial port
 * by calling the `SerialportWrite` function for each character until the null terminator is encountered.
 *
 * @param str A pointer to the null-terminated string to be written to the serial port.
 */
void SerialportWriteStr(char* str){
    for(int i = 0; str[i] != '\0'; ++i){
        SerialportWrite(str[i]);
    }
}


/**
 * @brief Writes a single character to the serial port.
 *
 * This function waits until the serial port is ready to send data by checking if the Transmit Holding Register (THR) is empty.
 * Once the serial port is ready, it writes the given character to the serial port.
 *
 * @param a The character to be written to the serial port.
 */
void SerialportWrite(char a)
{
    while (SerialSendReady() == 0);

    outportb(PortAddress, a);
}

/**
 * @brief Checks if the serial port is ready to send data.
 *
 * This function reads the Line Status Register (LSR) of the serial port and checks if the Transmit Holding Register (THR) is empty.
 * It determines if the serial port is ready to send data.
 *
 * @return A non-zero value if the serial port is ready to send data; returns 0 if it is not ready.
 */
int SerialportSerialSendReady()
{
    return inportb(PortAddress + 5) & 0x20;
}



// char SerialportRead()
// {
//     while (SerialReceiveReady() == 0);

//     return inportb(PortAddress);
// }

/**
 * Initialize the serial port for communication.
 *
 * This function initializes the serial port for communication by configuring the necessary settings.
 * It performs the following steps:
 *
 * 1. Set the `PortAddress` to the specified `port`.
 * 2. Disable all interrupts by writing 0x00 to the appropriate port address.
 * 3. Enable DLAB (set baud rate divisor) by writing 0x80 to the appropriate port address.
 * 4. Set the divisor to 3 (lo byte) to achieve a baud rate of 38400.
 * 5. Set the divisor to 3 (hi byte).
 * 6. Configure the serial port settings: 8 bits, no parity, one stop bit.
 * 7. Enable the FIFO (First-In-First-Out) buffer, clear it, and set the threshold to 14 bytes.
 * 8. Enable IRQs (Interrupt Requests) and set RTS/DSR.
 * 9. Set the `ConsoleInitialized` flag to true.
 *
 * @param port The COM port to initialize.
 *
 * @return None.
 *
 * @throws None.
 */
void SerialportInit(enum COMPort port)
{
    PortAddress = port;

    outportb(PortAddress + 1, 0x00);    // Disable all interrupts
    outportb(PortAddress + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outportb(PortAddress + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outportb(PortAddress + 1, 0x00);    //                  (hi byte)
    outportb(PortAddress + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(PortAddress + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(PortAddress + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    ConsoleInitialized = true;
}

/**
 * Check if data is available to be received from the serial port.
 *
 * This function checks if data is available to be received from the serial port by reading the appropriate port address.
 * It performs the following steps:
 *
 * 1. Read the value from the appropriate port address.
 * 2. Mask the value with 0x01 to check if the least significant bit is set.
 * 3. Return 1 if the least significant bit is set, indicating that data is available to be received.
 * 4. Return 0 otherwise.
 *
 * @return 1 if data is available to be received, 0 otherwise.
 *
 * @throws None.
 */
int SerialportSerialReceiveReady()
{
    return inportb(PortAddress + 5) & 1;
}

/**
 * Write a null-terminated string to the console.
 *
 * This function writes a null-terminated string character by character to the console.
 * It performs the following steps:
 *
 * 1. Iterate over each character in the string.
 * 2. Call the `Write` function to write each character to the console.
 *
 * @param str The null-terminated string to be written.
 *
 * @return None.
 *
 * @throws None.
 */
void WriteStr(char* str)
{
    for(int i = 0; str[i] != '\0'; ++i)
        Write(str[i]);
}
