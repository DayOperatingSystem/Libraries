#include <sleep.h>
#include <syscall.h>
#include <arch.h>

void sleep(unsigned int time)
{
	syscall1(SYSCALL_SET_TIMER, time);
}
