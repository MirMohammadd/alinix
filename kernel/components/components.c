#include <alinix/system/component.h>

SystemComponent* SystemComponent_create(char* name, char* description) {
    SystemComponent* component = (SystemComponent*)malloc(sizeof(SystemComponent));
    component->Name = (char*)malloc(strlen(name) + 1);
    strcpy(component->Name, name);
    component->Description = (char*)malloc(strlen(description) + 1);
    strcpy(component->Description, description);
    return component;
}