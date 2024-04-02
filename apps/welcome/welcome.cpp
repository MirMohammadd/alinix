#include <new.h>
#include <gui/gui.h>
#include <gui/widgets/button.h>
#include <gui/widgets/control.h>
#include <gui/widgets/scrollbar.h>
#include <gui/widgets/window.h>
#include <gui/directgui.h>
#include <convert.h>
#include <string.h>
#include <log.h>
#include <proc.h>


using namespace LIBHeisenKernel;
using namespace LIBHeisenKernel::Imaging;

char* path = "B:\\boot.jpg";

Window* welcomeWindow = 0;

void ValueChange(void *s,int v){
    welcomeWindow->backColor = v * 1000;
}


int main(){
    Log(Info,"Welcome to the Heisen OS!!!");
    GUI::SetDefaultFont();

    welcomeWindow = new Window(600, 600, 300, 300);
    welcomeWindow->titleString = "Welcome to the Heisen OS!";

    ScrollBar* scroll = new ScrollBar(Vertical);
    scroll->x = 100;
    scroll->y = 200;

    scroll->value.onChanged += ValueChange;
    welcomeWindow->AddChild(scroll);


    while (GUI::HasItems()){
        GUI::DrawGUI();
        GUI::ProcessEvents();
        //scroll->value += 1;
        if(scroll->value >= scroll->maxValue) {
            scroll->value = 0;
            scroll->maxValue += 20;
        }
    }
    return 0;
}