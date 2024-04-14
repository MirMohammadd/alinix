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
 * @file init.h

 */

#ifndef _ALINIX_INIT_H
#define _ALINIX_INIT_H

#include <alinix/types.h>




bool Initialize();
CommandBlockWrapper SCSIPrepareCommandBlock(uint8_t command, int length, uint64_t lba, int sectors);
bool ResetRecovery();
bool SCSIRequest(CommandBlockWrapper* request, uint8_t* dataPointer, int dataLength);
void DeInitialize();
char ReadSector(uint32_t lba, uint8_t* buf);
char WriteSector(uint32_t lba, uint8_t* buf);


#endif /*_ALINIX_INIT_H*/