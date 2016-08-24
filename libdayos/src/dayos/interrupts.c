#include <dayos/interrupts.h>
#include <dayos/syscall.h>
#include <arch.h>

int register_handler_process(int irqno)
{
	return syscall1(SYSCALL_REGISTER_ISR, irqno);
}

int reset_handler_process(int irqno)
{
	return syscall1(SYSCALL_REMOVE_ISR, irqno);
}
