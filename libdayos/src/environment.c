#include <stdlib.h>
#include <dayos.h>
#include <string.h>

static size_t environ_size = 0;
extern char** environ;

char* getenv(const char* name)
{
	for(size_t i = 0; i < environ_size; i++)
		if(strstr(environ[i], name) == environ[i])
			return strchr(environ[i], '=') + 1;

	return NULL;
}

/// FIXME: Specs say "don't copy" but should we?
int putenv(char* name)
{
	environ = (char**) realloc(environ, (environ_size + 2) * sizeof(char**));

	environ[environ_size] = name;
	environ_size++;
	environ[environ_size] = NULL;
}