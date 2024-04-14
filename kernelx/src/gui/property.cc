#include <gui/property.hpp>
#include <gui/widgets/control.hpp>

using namespace LIBHeisenKernel;

void LIBHeisenKernel::UpdateGUIPropertyTargetGUI(Control* target)
{
    if(target) target->ForcePaint();
}