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
 * @file syscall.h

 */
#ifndef __ALINIX_SYS_CALL_HEADER_H_
#define __ALINIX_SYS_CALL_HEADER_H_

enum Systemcalls {
        SYSCALL_EXIT = 0, // Tells kernel that procces is done and can be removed

        /////////////
        // Logging
        /////////////
    
        SYSCALL_LOG,
        SYSCALL_PRINT,

        /////////////
        // VFS
        /////////////

        SYSCALL_FILE_EXISTS,
        SYSCALL_DIR_EXISTS,
        SYSCALL_GET_FILESIZE,
        SYSCALL_READ_FILE,
        SYSCALL_WRITE_FILE,
        SYSCALL_CREATE_FILE,
        SYSCALL_CREATE_DIRECTORY,
        SYSCALL_EJECT_DISK,

        //////////////
        // GUI
        //////////////
        
        SYSCALL_GUI_GETLFB,
        SYSCALL_GET_SCREEN_PROPERTIES,

        //////////////
        // Memory
        //////////////

        SYSCALL_GET_HEAP_START,
        SYSCALL_GET_HEAP_END,
        SYSCALL_SET_HEAP_SIZE,
        SYSCALL_CREATE_SHARED_MEM,
        SYSCALL_REMOVE_SHARED_MEM,
        SYSCALL_MAP_SYSINFO,

        //////////////
        // Scheduler
        //////////////

        SYSCALL_RUN_PROC,
        SYSCALL_SLEEP_MS,
        SYSCALL_START_THREAD,
        SYSCALL_YIELD,
        SYSCALL_PROC_EXIST,
        SYSCALL_UNBLOCK,
        SYSCALL_SET_SCHEDULER,
        SYSCALL_GET_ARGUMENTS,

        //////////////
        // IPC
        //////////////

        SYSCALL_IPC_SEND,
        SYSCALL_IPC_RECEIVE,
        SYSCALL_IPC_AVAILABLE,

        //////////////
        // Clock
        //////////////

        SYSCALL_GET_TICKS,
        SYSCALL_GET_DATETIME,

        //////////////
        // Power
        //////////////

        SYSCALL_SHUTDOWN,
        SYSCALL_REBOOT,

        //////////////
        // STDIO
        //////////////

        SYSCALL_READ_STDIO,
        SYSCALL_WRITE_STDIO,
        SYSCALL_REDIRECT_STDIO,
        SYSCALL_STDIO_AVAILABLE,

        //////////////
        // Listings
        //////////////

        SYSCALL_BEGIN_LISTING,
        SYSCALL_LISTING_ENTRY,
        SYSCALL_END_LISTING,
        SYSCALL_GET_SYSINFO_VALUE,

        //////////////
        // Other
        //////////////
        SYSCALL_SET_CACTUSOS_LIB = 0xFFFF,
    };

#ifdef __cplusplus
int DoSyscall(unsigned int intNum, unsigned int arg1 = 0, unsigned int arg2 = 0, unsigned int arg3 = 0, unsigned int arg4 = 0, unsigned int arg5 = 0);

#else 
int DoSyscall(unsigned int intNum, unsigned int arg1, unsigned int arg2, unsigned int arg3, unsigned int arg4, unsigned int arg5);

#endif

#endif /*__ALINIX_SYS_CALL_HEADER_H_*/