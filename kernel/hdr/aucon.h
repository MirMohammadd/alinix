#ifndef __AU_CONSOLE_H__
#define __AU_CONSOLE_H__

#include <aurora.h>

#define SCREEN_SETMODE    200
#define SCREEN_GETWIDTH   201
#define SCREEN_GETHEIGHT  202
#define SCREEN_GETBPP     203
#define SCREEN_SETBPP     204
#define SCREEN_UPDATE     205
#define SCREEN_GET_SCANLINE  206
#define SCREEN_GET_PITCH     207
#define SCREEN_REG_MNGR      208
#define SCREEN_GET_FB     209

typedef struct _aucon_ {
	uint32_t width;
	uint32_t height;
	uint32_t *buffer;
	uint32_t bpp;
	uint16_t scanline;
	uint32_t size;
	uint32_t pitch;
	bool early_mode;
}AuConsole;

/*
* AuConsoleInitialize -- initialize kernel direct screen
* console
* @param info -- Pointer to kernel boot info structure
*/
extern void AuConsoleInitialize(PKERNEL_BOOT_INFO info, bool early);

/*
* AuConsolePostInitialise -- initialise the post console process
* @param info -- pointer to kernel boot info structure
*/
extern void AuConsolePostInitialise(PKERNEL_BOOT_INFO info);

/*
* AuTextOut -- standard text printing function
* for entire kernel
* @param text -- text to output
*/
AU_EXTERN AU_EXPORT void AuTextOut(const char* text, ...);

/*
* AuConsoleEarlyEnable -- enables or disable early
* mode text output
* @param value -- boolean value
*/
void AuConsoleEarlyEnable(bool value);

#endif