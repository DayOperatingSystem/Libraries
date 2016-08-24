#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>
#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void request_mem_region(const char* name, uintptr_t addr, size_t sz);

#ifdef __cplusplus
}
#endif
#endif