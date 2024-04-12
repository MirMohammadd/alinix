#ifndef _HEISEN_KERNEL_APPS_WELCOME_H
#define _HEISEN_KERNEL_APPS_WELCOME_H

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

static void helpButtonCallback(void *sender,MouseButtonArgs args);
static void exitButtonCallback(void *sender,MouseButtonArgs args);
static void rebootSystemAndSayGoodBye(void *sender,MouseButtonArgs args);
static void moreTipsHelpMenu(void *sender,MouseButtonArgs args);

#endif // _HEISEN_KERNEL_APPS_WELCOME_H