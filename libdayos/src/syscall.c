#include <syscall.h>
#include <arch.h>

inline int syscall1(int syscall, int ebx)
{
	int ret;
	asm("int $0x30" : : "a" (syscall), "b"(ebx));
	asm("movl %%eax, %0;" : "=r" (ret));

	return ret;
}

inline int syscall2(int syscall, int ebx, int ecx)
{
	int ret;
	asm("int $0x30" : : "a" (syscall), "b"(ebx), "c"(ecx));
	asm("movl %%eax, %0;" : "=r" (ret));

	return ret;
}

inline int syscall3(int syscall, int ebx, int ecx, int edx)
{
	int ret;
	asm("int $0x30" : : "a" (syscall), "b"(ebx), "c"(ecx), "d"(edx));
	asm("movl %%eax, %0;" : "=r" (ret));

	return ret;
}

void* sbrk(size_t size)
{
	return (void*) syscall1(SYSCALL_SBRK, size);
}
