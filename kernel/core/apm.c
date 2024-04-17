#include <alinix/apm.h>


char* GetComponentName(SystemComponent* component) {
    return component->Name;
}

char* GetComponentDescription(SystemComponent* component) {
    return component->Description;
}


APMController* APMController_create();