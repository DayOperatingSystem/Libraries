#include <stdlib.h>
#include <stdio.h>
#include <dayos/syscall.h>
#include <dayos/message.h>
#include <string.h>
#include <unistd.h>
#include <arch.h>

int system(const char* command)
{
	return 1;
}

pid_t fork()
{
	syscall1(SYSCALL_FORK, 0);
}
