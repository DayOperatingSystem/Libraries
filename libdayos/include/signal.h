#ifndef SIGNAL_H
#define SIGNAL_H

#define SIGINT 2
#define SIGILL 4
#define SIGFPE 8
#define SIGSEGV 11
#define SIGTERM 15
#define SIGBREAK 21
#define SIGABRT 22
#define NSIG 23
#define SIGHUP 24
#define SIGQUIT 25

#define SIG_DFL 0
#define SIG_IGN 1
#define SIG_ERR 2
#define SIG_HOLD 3

#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	
typedef int sigset_t;
typedef int sig_atomic_t; 

void (*signal(int sig, void (*func)(int)))(int);
int raise(int sig);
int kill(pid_t pid, int sig);

#ifdef __cplusplus
}
#endif

#endif
