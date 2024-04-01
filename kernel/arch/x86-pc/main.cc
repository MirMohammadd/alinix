#include <new.hpp>
#include <gui/gui.hpp>
#include <gui/widgets/button.hpp>
#include <gui/widgets/control.hpp>
#include <gui/widgets/scrollbar.hpp>
#include <gui/widgets/window.hpp>
#include <gui/directgui.hpp>
#include <convert.hpp>
#include <string.hpp>
#include <log.hpp>
#include <proc.hpp>

using namespace LIBCactusOS;

Window* mainWindow = 0;

void ValueChanged(void* s, int v)
{
    mainWindow->backColor = v * 1000;
}

int main(int argc, char** argv)
{
    GUI::SetDefaultFont();

    mainWindow = new Window(600, 600, 300, 300);
    mainWindow->titleString = "CactusOS File Browser";

    ScrollBar* scroll = new ScrollBar(Vertical);
    scroll->x = 100;
    scroll->y = 200;
    scroll->value.onChanged += ValueChanged;
    mainWindow->AddChild(scroll);

    while (GUI::HasItems()) {
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