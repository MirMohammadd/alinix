#include <gui/context.h>
#include <gui/widgets/button.h>
#include <gui/widgets/label.h>
#include <gui/directgui.h>
#include <gui/widgets/control.h>
#include <log.h>
#include <hardware/ata.hpp>


using namespace LIBHeisenKernel;
char* path = "B:\\settings.jpg";



void CapacityDriveCallback(void* sender, MouseButtonArgs args){
    double size = getDriveSize(0);
    Print("Drive Size: %f\n", size);
    
}

void SystemArgumentsCallBack(void* sender, MouseButtonArgs args){
    Window* SystemWindow = new Window(400, 300, 0, 0);
    Button* CapacityDiskButton = new Button("Capacity Disk");
    SystemWindow->titleString = "System Settings";
    SystemWindow->backColor = 0xFF150534;
    SystemWindow->height = 300;
    SystemWindow->width = 400;
    CapacityDiskButton->width = 300 - 2;
    CapacityDiskButton->height = 49;
    CapacityDiskButton->y = 50;
    CapacityDiskButton->x = 1;
    SystemWindow->AddChild(CapacityDiskButton);
    
    Print("Opened System Settings\n");

    

    
}

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
    SystemButton->MouseClick += SystemArgumentsCallBack;
}

