#include <io/video.h>
#include <lib/stdio.h>
#include <fcntl.h>

#include "commands.h"
#include "shell.h"

int argc;
char **argv;

void alogo(){
    _kcolor(BRIGHT_GREEN);
    printf("            _                                            _ \n");
    printf("  /\\  /\\___(_)___  ___ _ __     /\\ /\\___ _ __ _ __   ___| |\n");
    printf(" / /_/ / _ \\ / __|/ _ \\ '_ \\   / //_// _ \\ '__| '_ \\ / _ \\ |\n");
    printf("/ __  /  __/ \\__ \\  __/ | | | / __ \\  __/ |  | | | |  __/ |\n");
    printf("\\/ /_/ \\___|_|___/\\___|_| |_| \\/  \\/\\___|_|  |_| |_|\\___|_|");
    _kcolor(WHITE);

}


void help(){

}

void pwd(){
    printf("%s\n",current_user.cur_path);
}


void newfile(){
	if(argc!=2){
		printf("Bad usage. Try newfile --help for more informations\n");
	}
	else {
		if(strcmp(argv[1], "--help")==0) {
			printf("newfile FILENAME - Make a new file, and prompt for it's content\n");
		}
		else {
			int fd;			
			fd = open(argv[1], O_RDONLY);
			if(fd>=0) printf("-ERROR: %s File already exist\n", argv[1]);
			else {
				char text[256];
				printf("Filename: %s\n", argv[1]);
				close(fd);
				fd = open(argv[1], O_RDWR|O_CREAT|O_APPEND);		
				if(fd>=0){ 
					printf("Type your text here, actually only one line available!!\n");
					scanf("%s", text);
					write(fd,text, strlen(text));
					if(close(fd)==-1) printf("something went wrong\n");
				}
			}
		}
	}
}

void whoami(){
    printf("%s\n", current_user.username);
}