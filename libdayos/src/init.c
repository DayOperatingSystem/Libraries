#include <dayos.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <string.h>
#include <fcntl.h>

extern void InitHeap();
extern void init_signals();

//void* __stack_chk_guard = NULL;

#include <stdint.h>
#include <stdlib.h>

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

char** environ = NULL;
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void setup_stack_chk()
{
	//srand(clock());
	//__stack_chk_guard = rand();
	//srand(0);
}
 
void __attribute__((noreturn)) __stack_chk_fail()
{ 
	debug_printf("Stack overflow/corruption detected!");
	
	asm("int $0x1");
	exit(-1);
}

static void send_args(const char* path, int argc, char* argv[], pid_t pid)
{
	message_t msg;
	msg.signal = SIGNAL_OK;
	msg.size = argc + 1;
	send_message(&msg, pid);
	
	strcpy(msg.message, path);
	send_message(&msg, pid);
	
	if(!argv)
		return;
	
	for(int i = 0; i < argc; i++)
	{
		if(argv[i])
		{
			strcpy(msg.message, argv[i]);
			send_message(&msg, pid);
		}
	}
}

size_t count_environ(char** env)
{
	size_t i = 0;
	while(env[i]) i++;
	return i;
}

static void send_env(char* environ[], pid_t pid)
{
	message_t msg;
	msg.signal = SIGNAL_OK;
	msg.size = count_environ(environ);
	send_message(&msg, pid);

	size_t sz = msg.size;
	for(size_t i = 0; i < sz; i++)
	{
		strcpy(msg.message, environ[i]);
		send_message(&msg, pid);
	}
}

#define RECEIVE(msg, pid) while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);
static char** receive_args(int* argc)
{
	if(!argc)
		return NULL;
	
	message_t msg;
	if (receive_message_timeout(&msg, MESSAGE_ANY, 10, 1) == MESSAGE_ERR_RECEIVE)
		return NULL;
	
	*argc = msg.size;
	char** argv = malloc(sizeof(char*) * msg.size);
	
	for(int i = 0; i < msg.size; i++)
	{
		RECEIVE(msg, MESSAGE_ANY);
		argv[i] = strdup(msg.message);
	}
	
	return argv;
}

static void receive_env()
{
	message_t msg;
	if (receive_message_timeout(&msg, MESSAGE_ANY, 10, 1) == MESSAGE_ERR_RECEIVE)
		return;

	size_t count = msg.size;
	//char** argv = malloc(sizeof(char*) * msg.size);

	for(int i = 0; i < count; i++)
	{
		RECEIVE(msg, MESSAGE_ANY);
		putenv(strdup(msg.message));
		//argv[i] = strdup(msg.message);
	}
}


int execute_program(const char* path, int argc, char* argv[])
{
	FILE* exec = fopen(path, "r");
	
	if(!exec)
	{
		return 0;
	}
	
	char* content;
	fseek(exec, 0, SEEK_END);
	size_t sz = ftell(exec);
	fseek(exec, 0, SEEK_SET);

	content = (char*) malloc(sz);	
	fread(content, sz, 1, exec);

	pid_t pid = syscall2(9, (uintptr_t) content, (uintptr_t) path);
	
	fclose(exec);
	free(content);
	
	send_args(path, argc, argv, pid);
	send_env(environ, pid);

	return pid;
}

extern FILE* fd2file(int fd);
char** init_libdayos(int* argc)
{
	setup_stack_chk();
	InitHeap();
	init_signals();

	char** argv = NULL;
	pid_t vfs_service = get_service_pid("vfs");
	
	// FIXME: Get from kernel somehow!
	if(vfs_service)
	{
		argv = receive_args(argc);
		receive_env();

		int fdin, fdout, fderr;

		fdin = open("/dayos/dev/tty0", O_RDONLY);
		fdout = open("/dayos/dev/tty0", O_WRONLY);
		fderr = open("/dayos/dev/tty0", O_WRONLY);
		
		stdin = fopen("/dayos/dev/tty0", "r");
		stdout = fopen("/dayos/dev/tty0", "w");
		stderr = fopen("/dayos/dev/tty0", "w");
		
	}
	else
		debug_printf("No VFS available!\n");
	
	return argv;
}










