/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg

 */
#include <arch/x86-pc/io/vga.h>
#include <arch/x86-pc/io/keyboard.h>
#include <lib/status.h>
#include <lib/libc.h>
#include <lib/queue.h>

#include "shell.h"
#include "console.h"
#include "terminal.h"
#include "string.h"

#define CONSOLE_BUFFER_LENGTH 64

char buffer[200];

uint16_t keyIndex = 0;

command_t commands[10];
uint8_t commandIndex = 0;


struct console
{
	char	buffer[CONSOLE_BUFFER_LENGTH];
	uint8_t buffer_read;
	uint8_t buffer_write;
	uint8_t mode;
	void	(*write)(uchar_t c);

	TAILQ_ENTRY(console) next;
};

TAILQ_HEAD(, console) consoles_list;

ret_t console_setup(struct console **terminal_out,
		void (*write_function)(uchar_t c))
{
	struct console *terminal;

	TAILQ_INIT(&consoles_list);

	terminal = malloc(sizeof(struct console));

	if (!terminal)
		return -KERNEL_NO_MEMORY;

	memset(terminal->buffer, 0, sizeof(terminal->buffer));
	terminal->write        = write_function;
	terminal->buffer_read  = 0;
	terminal->buffer_write = 0;
	terminal->mode         = CONSOLE_MODE_CANON;

	TAILQ_INSERT_TAIL(&consoles_list, terminal, next);

	keyboard_setup(terminal);

	*terminal_out = terminal;

	return KERNEL_OK;
}


ret_t console_read(struct console *t,
		uchar_t *dst_buffer,
		size_t len)
{
	size_t count = 0;

	if (len == 0)
		return KERNEL_OK;

	while (1)
	{
		char c;

		/* No character available,  Wait until console_add_character()
		 * wakes us up */
		if (t->buffer_read == t->buffer_write)
		{
			/* Loop, maybe the semaphore was stolen by someone else */
			continue;
		}

		c = t->buffer[t->buffer_read];

		/* Copy the received character from the ring buffer to the
		 * destination buffer */
		memcpy((void *)dst_buffer,
				(void *)&t->buffer[t->buffer_read],
				sizeof(char));

		dst_buffer++;

		/* Update the ring buffer read pointer */
		t->buffer_read++;

		if (t->buffer_read == CONSOLE_BUFFER_LENGTH)
			t->buffer_read = 0;

		count++;

		if (t->mode & CONSOLE_MODE_ECHO)
			t->write(c);

		/* Did we read enough bytes ? */
		if (count == len || (c == '\n' && t->mode & CONSOLE_MODE_CANON))
			break;
	}

	return KERNEL_OK;
}


void console_write(struct console *t, void *src_buffer, uint16_t len)
{
	int i;
	char c;

	for (i = 0; i < len; i++)
	{
		memcpy((void *)&c, (void *)src_buffer, sizeof(char));
		len = i;

		t->write(c);

		src_buffer++;
	}
}


void console_set_mode(struct console *cons, uint8_t mode)
{
	cons->mode = mode;
}

void console_add_character(struct console *cons, char c)
{
	cons->buffer[cons->buffer_write] = c;
	cons->buffer_write++;

	if (cons->buffer_write == CONSOLE_BUFFER_LENGTH)
		cons->buffer_write = 0;

}


void shellHandlerKey(int32_t keycode,char ch){
    /*This will write a terminal in case of having a character*/
    if (keycode > 0 && keyIndex + 1 < 200 && ch != '\n'){
        terminal_write_next_char(ch);
        buffer[keyIndex] = ch;
        keyIndex++;
    }

    if (ch == "\n"){
        terminal_write_next_char('\n');
        shellHandleCommand();
        shellPrintKernel();
    }

  if(keycode == BACKSPACE) {
    //protect the 'kernel>' prefix
    if(terminal_getX() > 7) {
      terminal_backspace();
      //backspace command buffer as well
      buffer[keyIndex] = 0;
      keyIndex--;
    }
  }

  if (keycode == ESCAPE){
    terminal_clear();
    shellPrintKernel();
    shellResetBuffer();
  }

  if (keycode == PAGEUP){
    terminal_up();
  }

  if (keycode == PAGEDOWN){
    terminal_replay_future();
  }


}

void helpMenu(char* args){
    for (uint8_t i = 0;i<commandIndex;i++){
        print(commands[i].command);
        print(" - ");
        println(commands[i].description);
    }
}


void pong(char* args) {
  println("PONG!");
}

void cls(char* args) {
  terminal_clear();
}

void echo(char* args) {
  if(!args){
    println("");
    return;
  }
  println(args);
}

void TODO(char* args) {
  println("- Figure out how to interface with the IDE controller");
  println("- Create a filesystem driver, probably ext2.");
  println("- Add a better memory allocator, including the reuse of memory");
}

void linebreak(char* args) {
  terminal_linebreak();
}

void command_color(char* args){
  int len = strlen(args);
  if(len != 2 || !args) {
    println("Incorrect use of color, provide 2 characters only.");
    println("ex: color FF");
    println("The first color is background.");
    println("The second color is foreground.");
    println("0 - black        9  - light blue");
    println("1 - blue         A - light green");
    println("2 - green        B - light cyan");
    println("3 - cyan         C - light red");
    println("4 - red          D - light magenta");
    println("5 - magenta      E - yellow");
    println("6 - brown        F - white");
    println("7 - light gray");
    println("8 - dark gray");
    return;
  }

  terminal_set_color(hexchar_to_decimal(args[0]), hexchar_to_decimal(args[1]));
  terminal_clear();
}

void shell_initialize() {
  print("Initializing shell...\t");
  memset(commands, sizeof(commands), 0);
  registerCommand("help", helpMenu, "Displays this menu.");
  registerCommand("ping", pong, "Responds with PONG!");
  registerCommand("cls", cls, "Clears the terminal.");
  registerCommand("todo", TODO, "Prints the short term list of things to do.");
  registerCommand("echo", echo, "Print given string.");
  registerCommand("break", linebreak, "Print a red separating line.");
  registerCommand("color", command_color, "Set the terminal colors.");
  print("done");
  terminal_linebreak();
  shellPrintKernel();
}

void shellPrintKernel() {
  uint8_t color = terminal_get_color();
  terminal_set_color(terminal_get_background(), 0xC);
  print("kernel>");
  terminal_set_color_code(color);
}
typedef void func(char* parameters);


void shellHandleCommand() {
  char* cmd_buf = (char*)kalloc(sizeof(char) * (keyIndex + 1));
  cmd_buf[keyIndex] = 0;
  memcpy(buffer, cmd_buf, keyIndex);
  int len = strlen(cmd_buf);
  shell_reset_buffer();

  int space_index = string_index_of_char(cmd_buf, ' ');
  char* command;
  char* parameters;

  if(space_index >= 0){
    command = substring(cmd_buf, 0, space_index);
    parameters = substring(cmd_buf, space_index + 1, len);
  }else{
    command = cmd_buf;
    parameters = 0;
  }

  //see if the command exists
  uint8_t handled = 0;
  for(int i = 0; i < commandIndex; i++){
    if(strcmp(command, commands[i].command)){
      ((func*)commands[i].callback)(parameters);
      handled = 1;
      break;
    }
  }
  if(!handled) {
    println("Command not recognized! Type 'help' for some commands.");
  }
}


void shellResetBuffer() {
  keyIndex = 0;
  memset(buffer, sizeof(buffer), 0);
}

void registerCommand(char* command, void* callback, char* description) {
  command_t newcommand;
  newcommand.command = command;
  newcommand.callback = callback;
  newcommand.description = description;
  commands[commandIndex] = newcommand;
  commandIndex++;
}