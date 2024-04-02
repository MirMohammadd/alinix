#include <system/syscalls/implementations/linux.h>

#include <system/system.h>

using namespace HeisenOs;
using namespace HeisenOs::common;
using namespace HeisenOs::core;
using namespace HeisenOs::system;

CPUState* LinuxSyscalls::HandleSyscall(CPUState* state)
{
    switch (state->EAX)
    {
        case 0xFFFF: //We use this systemcall for setting the HeisenOs Syscall implementation for this process since linux is the default one
            //From now on this uses HeisenOs Systemcalls
            System::scheduler->CurrentProcess()->syscallID = 1;
            //Return a succes
            state->EAX = System::scheduler->CurrentProcess()->id; //Return the pid
            break;
    
        default:
            state->EAX = 0;
            break;
    }

    return state;
}