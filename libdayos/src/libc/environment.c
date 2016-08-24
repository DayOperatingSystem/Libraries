#include <stdlib.h>
#include <dayos/dayos.h>
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

static void add_variable(char* name)
{
	environ = (char**) realloc(environ, (environ_size + 2) * sizeof(char**));

	environ[environ_size] = name;
	environ_size++;
	environ[environ_size] = NULL;
}

static size_t get_variable_id(char** env, size_t num, const char* name)
{
	const char* equals = strchr(name, '=');
	size_t size = equals - name;
	
	for(size_t i = 0; i < environ_size; i++)
		if(!strncmp(env[i], name, size))
			return i;
		
	return -1;
}

/// FIXME: Specs say "don't copy" but should we?
int putenv(char* name)
{
	size_t idx = get_variable_id(environ, environ_size, name);
	if(idx == -1)
		add_variable(name);
	else
		environ[idx] = name;
	
	return 0;
}
