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
 * @file vfs.h

 */

#ifndef VFS_H
#define VFS_H



#include <types.h>


#define MAX_DEVICES 26

/**
 * @note This data type will define usage of the file system VFS
*/

typedef struct {
    char name[32];
    uint32_t flags;
    uint32_t len;
    uint32_t eof;
    uint32_t dev;
    uint32_t current_cluster;
    uint32_t type;
}file;

typedef struct {
    void (*mount) ();
    void (*read) (file *f, char *str);
    void (*write) (file *f, char *str);
    void (*close) (file *f);
    file (*open) (char *name);
    void (*ls) (char *dir);
    file (*cd) (char *dir);
    int (*touch) (char *name);
    int (*delete) (char *name);
} filesystem;


#define FS_FILE     0
#define FS_DIR      1
#define FS_NULL     2

void vfs_init();
void vfs_ls();
void vfs_ls_dir(char *dir);
int vfs_cd(char *name);
int vfs_touch(char *name);
int vfs_delete(char *name);
file *vfs_file_open(char *name, char *mode);
file *vfs_file_open_user(char *name, char *mode);
void vfs_file_read(file *f, char *str);
void vfs_file_write(file *f, char *str);
void vfs_file_close(file *f);
void vfs_file_close_user(file *f);
int vfs_get_dev(char *name);
void vfs_mount(char *name);
void vfs_unmount(char *name);


#endif // VFS_H