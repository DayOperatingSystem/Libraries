#include <unistd.h>
#include <syscall.h>
#include <arch.h>

pid_t getpid()
{
	return syscall(SYSCALL_GET_PID);
}

pid_t getppid()
{
	return syscall(SYSCALL_GET_PARENT_PID);
}
