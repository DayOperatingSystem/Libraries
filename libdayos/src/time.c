#include <time.h>
#include <syscall.h>
#include <arch.h>
#include <dayos.h>

// FIXME: Implementation!
clock_t clock()
{
	return syscall1(SYSCALL_GET_TICKS, 0);
}

// FIXME: Implementation!
time_t time(time_t* timer)
{
	time_t retval = clock() / CLOCKS_PER_SEC;
	if(timer)
		*timer = retval;

	return retval;
}

struct tm* gmtime(const time_t* timer)
{
	DSTUB;
	return NULL;
}

struct tm* localtime(const time_t* timer)
{
	DSTUB;
	return NULL;
}

size_t strftime(char* ptr, size_t maxsize, const char* format, const struct tm* timeptr)
{
	DSTUB;
	return 0;
}

time_t mktime(struct tm* timeptr)
{
	DSTUB;
	return 0;
}

double difftime(time_t end, time_t beginning)
{
	DSTUB;
	return 0;
}

char* ctime (const time_t* timer)
{
	DSTUB;
	return " ";
}

char* asctime(const struct tm* timeptr)
{
	DSTUB;
	return " ";
}

int gettimeofday(struct timeval* tp, void* tzp)
{
	tp->tv_sec = syscall1(SYSCALL_GET_TICKS, 0) / CLOCKS_PER_SEC;
	tp->tv_usec = 0; // TODO: High precision timer!
}