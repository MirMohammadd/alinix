#include <alinix/print.h>
#include <alinix/types.h>


void printfHex(uint8_t key){
    char *foo = "00";
    char *hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    Write(foo);
}