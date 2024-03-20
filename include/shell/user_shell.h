#ifndef USER_SHELL_H
#define USER_SHELL_H

typedef enum password_ctrl {
	NONE,
	CLEAR,
	MD5
} pwd_t;

struct passwd_user {
	char username[50];
	char password[50];
};

int user_chk(char *, char *);
int user_get(int, struct passwd_user *);
//int check_pwd(struct passwd, char*);
#endif