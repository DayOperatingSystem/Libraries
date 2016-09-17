#ifndef _PWD_H
#define _PWD_H

#include <sys/types.h>

struct passwd
{
	char* pw_name;
	uid_t pw_uid;
	gid_t pw_gid;
	char* pw_dir;
	char* pw_shell;
};

#ifdef __cplusplus
extern "C" {
#endif

struct passwd* getpwnam(const char*);

#ifdef __cplusplus
}
#endif

#endif
