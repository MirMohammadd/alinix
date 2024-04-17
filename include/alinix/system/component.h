#ifndef __ALINIX_KERNEL_COMPONENT_H
#define __ALINIX_KERNEL_COMPONENT_H

#include <alinix/memory.h>
#include <alinix/string.h>
#include <alinix/ulib.h>

typedef struct {
    char* Name;
    char* Description;
} SystemComponent;

SystemComponent* SystemComponent_create(char* name, char* description) ;

#endif 