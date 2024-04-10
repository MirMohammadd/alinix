#include <new.h>
#include <log.h>
#include <gui/widgets/button.h>
#include <gui/widgets/window.h>
#include <gui/directgui.h>
#include <random.h>
#include <datetime.h>
#include <time.h>
#include <convert.h>
#include <string.h>
#include <gui/widgets/label.h>

using namespace LIBHeisenKernel;

const int fieldWidth = 10;
const int fieldHeight = 10;
const int numOfMines = 16;


static const char multi_line_string[] = 
"Heisen Os , licensed under MIT license, written by Heisenberg and intended to provide utility for personal use\n"
"\n"
"\n";

int main(){
    GUI::SetDefaultFont();

    Window* mainWindow = new Window(600, 400, GUI::Width/2 - 300, GUI::Width/2 - 200);
    mainWindow->titleString = "Welcome to HeisenOs!";

    Control* control = new Control(600, 400, 0, 0);
    control->backColor = 0xFFBBBBBB;

    Button* helpMoreOptions = new Button("More Options");
    helpMoreOptions->width = 150 - 2;
    helpMoreOptions->height = 47;
    helpMoreOptions->x = 1;
    helpMoreOptions->y = 2;
    // helpMoreOptions->MouseClick += HelpMoreOptionsCallback;
}