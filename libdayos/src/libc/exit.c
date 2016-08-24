#include <stdlib.h>
#include <stdio.h>
#include <dayos/dayos.h>
#include <dayos/syscall.h>

void exit(int status)
{
	fflush(stdout);
	syscall1(SYSCALL_EXIT, status);
	for(;;);
}

void abort()
{
	exit(-1);
}
