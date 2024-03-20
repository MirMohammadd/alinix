#ifndef _DIRENT_H
#define _DIRENT_H

#include <types.h>
#define NAME_MAX 30

/*! 
    \struct dirent
    \brief Struttura dati che contiene le entry della cartella.
*/
struct dirent {
	ino_t d_ino;
	int d_type;
	char d_name[NAME_MAX+1];
};

/*! 
    \struct DIR
    \brief Struttura dati che contiene le informazioni su una cartella
*/
typedef struct 
{
  int handle; /**< Filesystem directory handle*/
  int cur_entry;
  char path[NAME_MAX + 1]; /**< dir path*/
  struct dirent entry; /**< Next directory item*/
} DIR;


int            closedir(DIR *);
DIR           *opendir(const char *);
struct dirent *readdir(DIR *);
int            readdir_r(DIR *, struct dirent *, struct dirent **);
void           rewinddir(DIR *);
void           seekdir(DIR *, long int);
long int       telldir(DIR *);
DIR* fake_opendir (const char *);
#endif