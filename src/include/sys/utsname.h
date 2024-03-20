#ifndef _UTSNAME_H
#define _UTSNAME_H

#define SYS_LEN 257

struct utsname {
  char  sysname[SYS_LEN];
  char  nodename[SYS_LEN];
                 
  char  release[SYS_LEN];
  char  version[SYS_LEN];
  char  machine[SYS_LEN];
};

int uname(struct utsname*);
  
#endif