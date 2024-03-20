#include <vfs.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#ifdef LEGACY
#include <kheap.h>
#endif
#ifdef LATEST
#include <heap.h>
#endif
#include <shell.h>

int cur_fd;

/**
  * @author Ivan Gualandri
  * @param char* path percorso del file da aprire
  * @param int oflags parametri di apertura
  *
  * Dato un path viene aperto se presente, e si torna il numero di descrittore che lo contiene
  * @todo Inserire gestione flags
  */
int open(const char *path, int oflags,  ...){
	int mpid;
	int ret_fd;
	char *newpath;
	va_list ap;
	va_start(ap, oflags);
	ret_fd = 0;		
    int opt_param_test;
	opt_param_test = va_arg(ap, int);
    printf("---------------------------------------\n");
    printf("Opening %s with flags %d and params %d \n", path, oflags, opt_param_test);
    printf("---------------------------------------\n");
	newpath = kmalloc(CURPATH_LEN * sizeof(char));
	memset(newpath, '\0', CURPATH_LEN);
	cur_fd=0;
	if(cur_fd == _SC_OPEN_MAX) cur_fd = 0;			

	while(fd_list[cur_fd].mountpoint_id != -1 && cur_fd < _SC_OPEN_MAX){
		//printf("%d %d\n", cur_fd, fd_list[cur_fd].mountpoint_id);		
		cur_fd++;
	}
	if(cur_fd == _SC_OPEN_MAX) {
		printf("No more file descriptors available\n");
		return -1;
	}
	strcpy(newpath, path);
    #ifdef DEBUG
    int error = 0;
	error = get_abs_path((char*) newpath);
	printf("Absolute path: %s %s\n\
            Return error code: %d", newpath, current_user.cur_path, error);
    #else
    get_abs_path((char*) newpath);
    #endif
    mpid = get_mountpoint_id((char*) newpath);		
	//printf("Cur_fd: %d\n",cur_fd);
	if(mpid >-1) {
		fd_list[cur_fd].mountpoint_id = mpid;				
		newpath = get_rel_path(mpid, (char *)newpath);		
	} else {
		printf("That path doesn't exist\n");
		va_end(ap);
		return -1;
	}
	if( mpid > -1 && mountpoint_list[fd_list[cur_fd].mountpoint_id].operations.open != NULL){
			fd_list[cur_fd].fs_spec_id = (int) mountpoint_list[fd_list[cur_fd].mountpoint_id].operations.open(newpath, oflags);
		if(fd_list[cur_fd].fs_spec_id == -1){
			printf("No file's Found\n");
			va_end(ap);
			return -1;
		}
	}
	else {
		if(mpid>-1) printf("No OPEN services found here\n");					
		//va_end(ap);
		return -1;
	}
	//va_end(ap)	
	fd_list[cur_fd].offset = 0;
	fd_list[cur_fd].flags_mask = oflags;
	ret_fd = cur_fd;
	cur_fd++;
	free(newpath);
	return ret_fd;
}
