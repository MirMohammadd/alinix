// #include <alinix/bootconsole.h>
// #include <alinix/types.h>


// /// @brief ///////////////////////////////
// int XOffset = 0;
// int YOffset = 0;
// uint8_t BackgroundColor = VGA_COLOR_BLACK; //Default console background color
// uint8_t ForegroundColor = VGA_COLOR_WHITE; //Default console foreground color
// // bool writeToSerial = false;

// static uint16_t* videoMemory = (uint16_t*)0xC00B8000;

// void Scroll(){
//     for (int i = 0; i < 24;i++){
//         for (int m = 0; m < 80;m++){
//             videoMemory[i * 80 + m] = videoMemory[(i + 1) * 80 + m];
//         }
//     }
//     for (int x = 0;x<80;x++){
//         uint16_t attrib = (BackgroundColor << 4) | (ForegroundColor & 0x0F);
//         volatile uint16_t * where;
//         where = (volatile uint16_t *)videoMemory + (24 * VGA_WIDTH + x) ;
//         *where = ' ' | (attrib << 8);
//     }
// }

// void Init(bool enableSerial){
//     writeToSerial = enableSerial;
//     if (enableSerial){
        
//     }
// }