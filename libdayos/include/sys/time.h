#ifndef __SYS_TIME_H
#define __SYS_TIME_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <kernelconfig.h>

struct timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
};

#ifdef __cplusplus
extern "C" {
#endif

int gettimeofday(struct timeval* tp, void* tzp);

#ifdef __cplusplus
}
#endif

#endif