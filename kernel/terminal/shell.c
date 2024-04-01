#include <io/video.h>

struct cmd shell_cmd[NUM_COM] = {
 { "aalogo",   aalogo,    "  -Show an ascii art logo" },
 { "clear",    _kclear,   "   Clear the screen" },
 { "poweroff", poweroff,  "Turn off the machine" },
 { "uname",    uname_cmd, "   Print kernel version, try uname --help for more info" },
 { "credits",  credits,   " Show DreamOS credits" },
 { "sleep",    sleep_cmd, "   Pause DreamOS for a particular number of seconds" },
 { "cpuid",    cpuid, 	  "   Show cpu identification informations" },
 { "date",     date, 	  "    Show date and time" },
 { "echo",     echo, 	  "    Print some lines of text" },
 { "help",     help,	  "    See the 'help' list to learn the DreamOS commands now available" },
 { "answer",   answer,    "  42" },
 { "drv_load", drv_load,  "Tool to load and kill drivers" },
 { "ls",       ls,        "      Tool for listing dir - not complete-" },
 { "cd",       cd,        "      Change dir - not complete-" },
 { "whoami",   whoami,    "  Show the current user name" },
 { "tester",   tester,    "  Try some functions, 'tester --help' for more info'" },
 { "pwd",      pwd,       "     Print current working directory" },
 { "more",     more,      "    Read content of a file" },
 { "newfile",  newfile,	  "	Create a new file"},
 { "ps", 	   ps,		  "	Show task list"},
};