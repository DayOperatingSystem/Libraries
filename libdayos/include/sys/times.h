#ifndef __SYS_TIMES_H
#define __SYS_TIMES_H

#include <sys/types.h>

struct tms
{
	clock_t tms_utime;
	clock_t tms_stime;
	clock_t tms_cutime;
	clock_t tms_cstime;
};

#ifdef __cplusplus
extern "C" {
#endif

clock_t times(struct tms*);

#ifdef __cplusplus
}
#endif

#endif