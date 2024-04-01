#ifndef __CONTEXTMANAGER_H
#define __CONTEXTMANAGER_H

#include <types.hpp>
#include <list.hpp>
#include <gui/contextinfo.hpp>

// Class that manages a list of contexts
class ContextManager
{
private:

public:
    // List of al contexts present on the desktop
    // Organized from top to bottom, so top context is at position 0
    List<ContextInfo*> contextList;

    // Initialize a new instance of the ContextManager
    ContextManager();

    // Destructor
    ~ContextManager();

    
    // Find the corresponding context at the position given by x and y
    // The order is from top to bottom!
    ContextInfo* FindTargetContext(int x, int y);

    // Find all contexts that exist in the given area
    List<ContextInfo*> FindTargetContexts(Rectangle area);

    // Move a context to the front of the desktop
    void MoveToFront(ContextInfo* info);
};

#endif