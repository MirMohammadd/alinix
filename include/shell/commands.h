#ifndef __COMMANDS_H
#define __COMMANDS_H

#include <shell.h>
#include <kheap.h>
#define MAX_TEST 16

extern int argc;
extern char **argv;

void aalogo();
void logo();
void help();
void echo();
void poweroff();
void kmalloc_try();
void do_fault();

void uname_cmd();
void uname_help();
void uname_info();
void printmem();
void credits();
void sleep_cmd();
void cpuid();
void answer();
void drv_load();
void ls();
void cd();
void whoami();
void tester();
void pwd();	
void more();
void newfile();
void ps();

struct devel {
	const char cmd_testname[CMD_LEN];
	void (*func)(void);
};

#endif