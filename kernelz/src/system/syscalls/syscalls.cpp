#include <system/syscalls/syscalls.h>

#include <system/system.h>
#include <system/syscalls/implementations/cactusos.h>
#include <system/syscalls/implementations/linux.h>

using namespace HeisenOs;
using namespace HeisenOs::common;
using namespace HeisenOs::system;
using namespace HeisenOs::core;

SystemCallHandler::SystemCallHandler()
: InterruptHandler(0x80) {

}

uint32_t SystemCallHandler::HandleInterrupt(uint32_t esp)
{
    //Interrupts need to be enabled for io system calls
    InterruptDescriptorTable::EnableInterrupts();

    int ID = System::scheduler->CurrentProcess()->syscallID;

    switch (ID)
    {
        case 0: //Linux Systemcall
            return (uint32_t)LinuxSyscalls::HandleSyscall((CPUState*)esp);
            break;
        case 1: //HeisenOs Systemcall
            return (uint32_t)CactusOSSyscalls::HandleSyscall((CPUState*)esp);
            break;   
        default:
            Log(Error, "Process %d has unkown syscallID %d", System::scheduler->CurrentProcess()->syscallID, ID);
            break;
    }

    //Restore previous state
    InterruptDescriptorTable::DisableInterrupts();

    return esp;
}