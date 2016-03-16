#include <sys/stat.h>
#include <fcntl.h>

int fstat(int fd, struct stat* stat)
{
	return -1;
}

mode_t umask(mode_t mode)
{
	return 0;
}

int fchmod(int fildes, mode_t mode)
{
	return 0;
}

int stat(const char* name, struct stat* stat)
{
	int fd = open(name, O_RDONLY);
	if(fd < 0) return -1;

	return fstat(fd, stat);
}