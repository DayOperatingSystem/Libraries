#include <sys/stat.h>
#include <fcntl.h>
#include <dayos/dayos.h>
#include <dayos/vfs.h>

extern FILE* fd2file(int fd); // From fcntl.c

int fstat(int fd, struct stat* stat)
{
	return vfs_stat(&fd2file(fd)->native_file, stat);
}

mode_t umask(mode_t mode)
{
	DSTUB;
	return 0;
}

int fchmod(int fildes, mode_t mode)
{
	DSTUB;
	return 0;
}

int stat(const char* name, struct stat* stat)
{
	int fd = open(name, O_RDONLY);
	if(fd < 0) return -1;

	return fstat(fd, stat);
}

int chdir(const char* path)
{
	DSTUB;
	return -1;
}

int rmdir(const char* path)
{
	DSTUB;
	return -1;
}

int mkdir(const char* name, mode_t mode)
{
	if(vfs_mkdir(name, mode) == SIGNAL_OK)
		return 0;
	
	return -1;
}
