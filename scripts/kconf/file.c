#include "dialog.h"
#include "lkc.h"


#define PATH_MAX        4096

FILE *zconf_fopen(const char *name)
{
	char *env, fullname[PATH_MAX+1];
	FILE *f;

	f = fopen(name, "r");
	if (!f && name != NULL && name[0] != '/') {
		env = getenv(SRCTREE);
		if (env) {
			snprintf(fullname, sizeof(fullname),
				 "%s/%s", env, name);
			f = fopen(fullname, "r");
		}
	}
	return f;
}