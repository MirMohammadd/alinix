#ifndef _VFS_H
#define _VFS_H

#include <dirent.h>
#include <stddef.h>
#include <unistd.h>
#include <use.h>
#include <sys/stat.h>

#define MAX_MOUNTPOINT 10
#define MAX_FD _SC_OPEN_MAX

#define FS_FILE 0x01
#define FS_DIRECTORY 0x02
#define FS_MOUNTPOINT 0x03


struct directory_operations {
	DIR* (*opendir_f)(const char *);
	int (*closedir_f)(DIR *dirp);
	struct dirent* (*readdir_f)(DIR *dirp);
};

struct super_node_operations {
	/*Qui vanno i puntatori alle funzioni sul supernode*/
	int (*open)(const char *, int, ... );
	int (*close)(int);
	ssize_t (*read)(int, char*, size_t);
	ssize_t (*write)(int,const void*, size_t);
};

struct stat_operations{
	int (*stat)(char*, struct stat*);
};

/*!  \struct mountpoint_t
     \brief Struttura dati che contiene le informazioni sui files system montati
 */
struct mountpoint_t {
		char mountpoint[64];/**< Indica il nome del mountpoint*/
		unsigned int pmask; /**< Maschera dei permessi*/
		unsigned int uid; /**< User ID*/
		unsigned int gid; /**< Group ID*/
		unsigned int start_address; /**< Indirizzo di partenza del FileSystem*/
		int dev_id; /**< Device ID*/		
		struct super_node_operations operations;
		struct directory_operations dir_op;
		struct stat_operations stat_op;
};

/*!  \struct file_descriptor
     \brief Struttura dati che contiene le informazioni su di un file aperto
 */

struct file_descriptor {
	int fs_spec_id; /**< Il descrittore del file interno del FileSystem*/
	int mountpoint_id; /**< L'id del mountpoint nel quale si trova il file */
	int offset; /**< Offset per lettura file, per la prossima read*/
	int flags_mask; /**<Flags per le modalita di apertura del file*/
};

//extern struct inode *root;
typedef struct file_descriptor file_descriptor_t;

extern int cur_fd;
extern file_descriptor_t fd_list[_SC_OPEN_MAX];
extern struct mountpoint_t mountpoint_list[MAX_MOUNTPOINT];

//void open_vfs (struct inode *);
//void close (int);
int get_mountpoint_id(char *);
char* get_rel_path(int, const char*);
int open_dir(char *);
//int read (int, void*, size_t);
//int write (int, void*, size_t);
int get_abs_path(char *);
void vfs_init();

#endif
