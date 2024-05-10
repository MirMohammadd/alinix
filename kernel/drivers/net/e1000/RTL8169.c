#include <net/RTL8169.h>
#include <alinix/init.h>
#include <alinix/kernel.h>
#include <alinix/port.h>

void getMacAddr(int macAddress[]){
    char i;
    for (i = 0;i < 6;i++){
        macAddress[i] = inportb(ioaddr + 1);
    }
     outportb(ioaddr + 0x37, 0x10); /*set the Reset bit (0x10) to the Command Register (0x37)*/
    while(inportb(ioaddr + 0x37) & 0x10);
}