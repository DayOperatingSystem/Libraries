#ifndef DAYOS_H
#define DAYOS_H

#include <arch.h>
#include "message.h"
#include "service.h"
#include "interrupts.h"
#include "vfs.h"
#include "sleep.h"

#include <unistd.h>
#define DSTUB { debug_printf("[ LIBDAYOS ] Library stub '%s' in process %d\n", __func__, getpid()); }

#ifdef __cplusplus
extern "C" {
#endif

int debug_printf(const char* fmt, ...);
void debug_putch(int c);
int execute_program(const char* path, int argc, char* argv[]);

#ifdef __cplusplus
}
#endif

#endif
