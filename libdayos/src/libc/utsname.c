#include <sys/utsname.h>
#include <dayos/syscall.h>
#include <string.h>
#include <arch.h>

int uname(struct utsname* name)
{
	if(!name)
		return -1;
	
	return syscall1(SYSCALL_VERSION, (uintptr_t) name);
}
