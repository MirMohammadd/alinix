/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg
 * @file ipc.cpp

 */
#include <ipc.h>
#include <proc.h>
#include <string.h>

using namespace LIBHeisenKernel;

int LIBHeisenKernel::IPCSend(int dest, int type, unsigned int arg1, unsigned int arg2, unsigned int arg3, unsigned int arg4, unsigned int arg5, unsigned int arg6)
{
    //Create IPCMessage
    IPCMessage message;
    message.dest = dest;
    message.type = type;
    message.source = Process::ID;
    
    //Copy args
    message.arg1 = arg1;
    message.arg2 = arg2;
    message.arg3 = arg3;
    message.arg4 = arg4;
    message.arg5 = arg5;
    message.arg6 = arg6;
    
    return IPCSend(message);
}

int LIBHeisenKernel::IPCSend(IPCMessage message)
{
    return DoSyscall(SYSCALL_IPC_SEND, (uint32_t)&message);
}

int LIBHeisenKernel::IPCAvailable()
{
    return DoSyscall(SYSCALL_IPC_AVAILABLE);
}

IPCMessage LIBHeisenKernel::ICPReceive(int fromID, int* errOut, int type)
{
    IPCMessage result;
    DoSyscall(SYSCALL_IPC_RECEIVE, (uint32_t)&result, fromID, (uint32_t)errOut, type);
    return result;
}