#include <io/video.h>
#include <lib/stdio.h>
#include <fcntl.h>

#include "commands.h"
#include "shell.h"

#include <stddef.h>
#include <dirent.h>

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

void cd( ){
	//char *relpath;		
	char abspath[CURPATH_LEN];
	DIR *dirp=NULL;	
	if(argc != 2) {
		printf("Bad usage. Try 'ls -l' and then 'cd dir'.\n");
		return;
	} else {
		int i=0;
		//int rel_size = 0;		
		memset(abspath, '\0', CURPATH_LEN);				
		if(argv[1][0] == '/') {
			i = get_mountpoint_id(argv[1]);		
			strcpy(abspath, argv[1]);
			//printf("abspath: %s\n", abspath);
			dirp=opendir(argv[1]);
		}
		else if(!strncmp(argv[1], "..", 2)) {
			printf(".. option %s\n", argv[1]);
			return;
		}
		else if(argv[1][0]=='.') {
			//printf(". option\n");			
			if(strlen(argv[1]) == 1) return;
			else printf("str_len: %d\n", strlen(argv[1]));
		}		
		else {			
			int abs_size = 0;			
			abs_size = strlen(current_user.cur_path);
			strcpy(abspath, current_user.cur_path);
			if(abspath[abs_size-1] == '/')
				strncat(abspath, argv[1], strlen(argv[1]));
			else {
				strncat(abspath, "/", strlen(argv[1]));
				strncat(abspath, argv[1], strlen(argv[1]));
			}	
			dirp=opendir(abspath);			
		}		
		if(dirp!=NULL){			
			closedir(dirp);
		}		
		//rel_size = strlen(argv[1]) - strlen(mountpoint_list[i].mountpoint);
		if(i == -1) {			
			printf("cd: %s: No such file or directory\n", argv[1]);
			return;
		}
		else {
			strcpy(current_user.cur_path, abspath);
		}
		/*if(rel_size >0){
			relpath = get_rel_path(i, argv[1]);
			free(relpath);
		}*/
	}
}

