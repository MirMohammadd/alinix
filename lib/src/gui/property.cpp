#include <gui/property.h>
#include <gui/widgets/control.h>

using namespace LIBHeisenKernel;

void LIBHeisenKernel::UpdateGUIPropertyTargetGUI(Control* target)
{
    if(target) target->ForcePaint();
}