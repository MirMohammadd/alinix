#include <gui/context.h>
#include <gui/widgets/button.h>
#include <gui/widgets/label.h>
#include <gui/directgui.h>
#include <gui/widgets/control.h>


using namespace LIBHeisenKernel;


int main(){
    GUI::SetDefaultFont();
    Window* mainWindow = new Window(800, 600, 0, 0);
    mainWindow->titleString = "Settings";
    mainWindow->backColor = 0xFF150534;

    Button* SystemButton = new Button("System");
    SystemButton->width = 130 -2;
    SystemButton->height = 47;
    SystemButton->x = 1;
    SystemButton->y = 2;
    SystemButton->MouseClick += SystemButtonCallback;
}

void SystemButtonCallback(void* sender, MouseButtonArgs arg){
    DoSyscall(SYSCALL_SHUTDOWN);
}