#include <setjmp.h>

#define OFS_EBP   "0"
#define OFS_EBX   "4"
#define OFS_EDI   "8"
#define OFS_ESI   "12"
#define OFS_ESP   "16"
#define OFS_EIP   "20"
/*
__attribute((naked)) int setjmp(jmp_buf env)
{

	asm volatile("movl 4(%esp), %edx");
	asm volatile("movl (%esp), %eax");
	asm volatile("movl %eax, " OFS_EIP "(%edx)");
	asm volatile("movl %ebp, " OFS_EBP "(%edx)");
	asm volatile("movl %ebx, " OFS_EBX "(%edx)");
	asm volatile("movl %edi, " OFS_EDI "(%edx)");
	asm volatile("movl %esi, " OFS_ESI "(%edx)");
	asm volatile("movl %esp, " OFS_ESP "(%edx)");
	asm volatile("xorl %eax, %eax");
	asm volatile("ret");
}

__attribute((naked)) void longjmp(jmp_buf env, int value)
{

	return;

	asm volatile("movl 4(%esp), %edx");
	asm volatile("movl 8(%esp), %esp");
	asm volatile("movl " OFS_ESP "(%edx), %esp");
	asm volatile("movl " OFS_EIP "(%edx), %ebx");
	asm volatile("movl %ebx, (%esp)");

	asm volatile("movl " OFS_EBP "(%edx), %ebp");
	asm volatile("movl " OFS_EBX "(%edx), %ebx");
	asm volatile("movl " OFS_EDI "(%edx), %edi");
	asm volatile("movl " OFS_ESI "(%edx), %esi");

	asm volatile("ret");
}
*/