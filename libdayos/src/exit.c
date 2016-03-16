#include <stdlib.h>
#include <dayos.h>
#include <syscall.h>

void exit(int status)
{
	syscall1(SYSCALL_EXIT, status);
	for(;;);
}

void abort()
{
	exit(-1);
}
