#include <alinix/types.h>
#include <alinix/enums.h>
#include <alinix/port.h>
#include <alinix/serialport.h>

enum COMPort PortAddress = COM1;
bool Initialized = false;

Init(enum COMPort port)
{
    PortAddress = port;

    outportb(PortAddress + 1, 0x00);    // Disable all interrupts
    outportb(PortAddress + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outportb(PortAddress + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outportb(PortAddress + 1, 0x00);    //                  (hi byte)
    outportb(PortAddress + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(PortAddress + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(PortAddress + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    Initialized = true;
}

void SerialportWriteStr(char* str){
    for(int i = 0; str[i] != '\0'; ++i){
        SerialportWrite(str[i]);
    }
}

int SerialportSerialSendReady()
{
    return inportb(PortAddress + 5) & 0x20;
}

char SerialportRead()
{
    while (SerialReceiveReady() == 0);

    return inportb(PortAddress);
}

char SerialportRead()
{
    while (SerialReceiveReady() == 0);

    return inportb(PortAddress);
}

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

    Initialized = true;
}