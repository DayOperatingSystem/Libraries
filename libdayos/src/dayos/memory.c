#include <arch.h>
#include <dayos/memory.h>
#include <dayos/syscall.h>

void request_mem_region(const char* name, uintptr_t addr, size_t sz)
{
	syscall3(SYSCALL_REQUEST_MEMORY_RANGE, (uintptr_t) name, addr, sz);
}
