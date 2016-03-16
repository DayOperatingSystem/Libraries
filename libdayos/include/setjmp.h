#ifndef SETJMP_H
#define SETJMP_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
	void* p[9];
} jmp_buf;

#ifdef __cplusplus
inline longjmp(jmp_buf env, int val)
{
	__builtin_longjmp(&env, val);
}
#endif

#define setjmp(x) __builtin_setjmp(&x)
#define longjmp(e,v) __builtin_longjmp(&e,v)

#endif
