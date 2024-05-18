#include <alinix/VTOC.h>
#include <alinix/memory.h>

void GetCHRFromVTOC(void *buffer){
    uint16_t cyl,head;
    uint8_t rec;
    memcpy(& cyl,buffer + 15,2);
    memcpy(&head,buffer + 17,2);
    memcpy(&rec,buffer + 19,1);
    RET;
}

