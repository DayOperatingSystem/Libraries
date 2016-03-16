#ifndef __UNISTD_H
#define __UNISTD_H

#include "stdint.h"
#include "stddef.h"
#include "fcntl.h"
#include "message.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define F_OK SIGNAL_OK

#define _SC_CLK_TCK 0 // HACK!

#ifdef __cplusplus
extern "C" {
#endif

extern char* optarg;
extern int optind, opterr, optopt;
int getopt(int argc, char* argv[], const char* opts);

long sysconf(int name);
pid_t getpid();
pid_t getppid();

#ifdef __cplusplus
}
#endif

#endif
