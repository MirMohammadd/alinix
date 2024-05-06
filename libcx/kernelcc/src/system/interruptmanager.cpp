/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/
#include <system/interruptmanager.h>

using namespace CactusOS;
using namespace CactusOS::common;
using namespace CactusOS::system;


InterruptHandler::InterruptHandler(uint8_t interruptNumber)
{
    InterruptManager::AddHandler(this, interruptNumber);
}

uint32_t InterruptHandler::HandleInterrupt(uint32_t esp)
{
    return esp;
}



List<InterruptHandler*>* InterruptManager::interruptCallbacks[256]; //Allows for multiple interrupt handlers per interrupt

void InterruptManager::Initialize()
{
    for(int i = 0; i < 256; i++)
    {
        interruptCallbacks[i] = 0;
    }
}

uint32_t InterruptManager::HandleInterrupt(uint8_t num, uint32_t esp)
{
    if(interruptCallbacks[num] == 0) //No list of callbacks present for specific interrupt
        return esp;
    
    if(interruptCallbacks[num]->size() == 0) //The list contains no handlers
        return esp;
    
    for(int i = 0; i < interruptCallbacks[num]->size(); i++)
    {
        InterruptHandler* handler = interruptCallbacks[num]->GetAt(i);
        esp = handler->HandleInterrupt(esp);
    }

    return esp;
}

void InterruptManager::AddHandler(InterruptHandler* handler, uint8_t interrupt)
{
    if(interruptCallbacks[interrupt] == 0)
        interruptCallbacks[interrupt] = new List<InterruptHandler*>(); //Create new list
    
    interruptCallbacks[interrupt]->push_back(handler);
}
void InterruptManager::RemoveHandler(InterruptHandler* handler, uint8_t interrupt)
{
    interruptCallbacks[interrupt]->Remove(handler);
    if(interruptCallbacks[interrupt]->size() == 0) {
        delete interruptCallbacks[interrupt];
        interruptCallbacks[interrupt] = 0;
    }
}