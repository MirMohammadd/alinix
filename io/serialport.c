#include <alinix/types.h>
#include <alinix/serialport.h>
#include <alinix/port.h>
#include <alinix/enums.h>

COMPort PortAddress = COMPort::COM1;

char Write(char a)
{
    while (SerialSendReady() == 0);

    outportb(PortAddress, a);
}