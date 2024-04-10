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
"\nIt is recommended to reboot your system after installing Os."
"\n";



/**
 * @brief Static functions that will be implemented on the help GUI menu
 * @todo call SYSCALL_EXIT (important! otherwise you'll have a memory leak)
*/

static void helpButtonCallback(void *sender,MouseButtonArgs args);
static void exitButtonCallback(void *sender,MouseButtonArgs args);
static void rebootSystemAndSayGoodBye(void *sender,MouseButtonArgs args);


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

    Button* shutdownAndReboot = new Button("Reboot and shutdown (recommended)");
    shutdownAndReboot->width = 300 - 2;
    shutdownAndReboot->height = 49;
    shutdownAndReboot->y = 50;
    shutdownAndReboot->x = 1;
    shutdownAndReboot->MouseClick += rebootSystemAndSayGoodBye;
    // helpMoreOptions->MouseClick += HelpMoreOptionsCallback;
}

void exitButtonCallback(void *sender,MouseButtonArgs args){
    /**
     * @brief This should be the sys exit call after user click on the close button
    */
    DoSyscall(SYSCALL_EXIT);
}

void rebootSystemAndSayGoodBye(void *sender,MouseButtonArgs args){
    DoSyscall(SYSCALL_REBOOT);
}