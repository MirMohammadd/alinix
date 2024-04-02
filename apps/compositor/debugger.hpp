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
 * @file debugger.hpp

 */
#ifndef __DEBUGGER_H
#define __DEBUGGER_H

#include "compositor.hpp"

class Compositor;

// Class used to display usefull debugging information when testing the compositor
class CompositorDebugger
{
private:
    // To which compositor is this debugger atached?
    Compositor* target = 0;
public:
    // Is the debugger enabled?
    bool enabled = false;

    // Create a new instance of a CompositorDebugger
    CompositorDebugger(Compositor* target);


    // Handle the debugging of one specific context
    // Called for every context every frame
    void ProcessContext(ContextInfo* ctx);

    // Handles any additional debugging for each frame
    void ProcessGeneral();
};

#endif