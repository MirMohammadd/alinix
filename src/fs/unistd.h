#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <vfs.h>

//file_descriptor_t fd_list[_SC_OPEN_MAX];

ssize_t read(int fildes, void *buf, size_t nbyte){
	int mp_id = 0;
	int fs_fd;
	mp_id = fd_list[fildes].mountpoint_id;
	fs_fd = fd_list[fildes].fs_spec_id;
	//printf("Mpoint id: %d Fs_fd: %d\n", mp_id, fs_fd);
	if (mountpoint_list[mp_id].operations.read != NULL)
		return mountpoint_list[mp_id].operations.read(fs_fd,(char *) buf, nbyte);
	else
		printf("No READ Found for that file system\n");
	return 0;
}

ssize_t write(int fildes, const void *buf, size_t nbyte){
	int fs_fd = 0;
	fs_fd = fd_list[fildes].fs_spec_id;
	if(fd_list[fildes].flags_mask&O_RDWR) {		
		printf("allright, let's go\n");
		printf("placeholder for write, coming soon,\n stay tuned\n");
		printf("Oh i received something: %s\n", buf);
		if((ssize_t*)mountpoint_list[fd_list[fildes].mountpoint_id].operations.write!=NULL)
			mountpoint_list[fd_list[fildes].mountpoint_id].operations.write(fs_fd,(void *) buf, nbyte);
		//else printf("Give Me a pen and i'll write you the world\n");
		else {
			printf("Give Me a pen and i'll write you the world\n");
			return -1;
		}
	}
	else return -1;
	return 0;
}

int close(int fildes){
	int mp_id;
	int fs_fd;
	mp_id = fd_list[fildes].mountpoint_id;
	fs_fd = fd_list[fildes].fs_spec_id;
	if (fd_list[fildes].fs_spec_id >= -1){
		if(mountpoint_list[mp_id].operations.close !=NULL)
			mountpoint_list[mp_id].operations.close(fs_fd);		
		fd_list[fildes].fs_spec_id = -1;
		fd_list[fildes].mountpoint_id = -1;
		return 0;
	}
	else
		return -1;

return 0;
}