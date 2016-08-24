#include <unistd.h>
#include <dayos/syscall.h>
#include <arch.h>

pid_t getpid()
{
	return syscall1(SYSCALL_GET_PID, 0);
}

pid_t getppid()
{
	return syscall1(SYSCALL_GET_PARENT_PID, 0);
}
