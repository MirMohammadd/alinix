#include <gui/context.h>
#include <gui/widgets/button.h>
#include <gui/widgets/label.h>
#include <gui/directgui.h>


using namespace LIBHeisenKernel;


int main(){
    GUI::SetDefaultFont();
    Context* mainScreen = GUI::RequestContext(160, 160, GUI::Width-160, 0);
    if(mainScreen == 0)
        return -1;

    DirectGUI::DrawString("Settings",3,14,0xFF000000);
    
}