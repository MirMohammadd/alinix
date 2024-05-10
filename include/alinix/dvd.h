#ifndef __ALINIX_KERNEL_DVD_H
#define __ALINIX_KERNEL_DVD_H

#include <alinix/types.h>

struct dvd{
    unsigned char hours;
    unsigned char minutes;
    unsigned char minute;
    unsigned char secs;
    unsigned char seconds;
    unsigned char milisec;

    unsigned char memory_secs;
    unsigned char memory_minutes;

    unsigned char number;
    unsigned char numberA0;
    unsigned char numberA1;
    unsigned char numberB0;
    unsigned char numberB1;
    unsigned char numberC0;
    unsigned char numberC1;
    unsigned char numberD0;
    unsigned char numberD1;
    unsigned char numberE0;
    unsigned char numberE1;
    unsigned char numberF0;
    unsigned char numberF1;

    unsigned char digit=0;
    unsigned char grid=0;
    unsigned char gridSegments = 0b00000011; // Here I define the number of GRIDs and Segments I'm using

    bool flag=true;
    bool flagSecs=false;


    unsigned int segOR[14];
};

#endif /* __ALINIX_KERNEL_DVD_H */