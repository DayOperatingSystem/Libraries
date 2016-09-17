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
#define SIGTSTP 26
#define SIGALRM 27
#define SIGPIPE 28
#define SIGUSR1 29
#define SIGUSR2 30
#define SIGTTIN 31

#define SIG_DFL (void (*)(int)) 0
#define SIG_IGN (void (*)(int)) 1
#define SIG_ERR (void (*)(int)) 2
#define SIG_HOLD (void (*)(int)) 3
#define SIG_BLOCK (void (*)(int)) 4
#define SIG_UNBLOCK (void (*)(int)) 5

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
