#include <termios.h>
#include <dayos/vfs.h>
#include <fcntl_extra.h>
#include <dayos/dayos.h>
#include <string.h>

int tcflush(int fd, int mode)
{
	if(!fdvalid(fd))
		return -1;
	
	FILE* file = fd2file(fd);
	fflush(file);
}

int tcgetattr(int val, struct termios* tios)
{
	// FIXME: Retrieve real settings!
	tios->c_iflag = BRKINT;
	tios->c_lflag = ECHO | ECHOE | ISIG | ICANON;

	return 0;
}

pid_t tcgetsid(int fd)
{
	if(!fdvalid(fd))
		return -1;
	
	FILE* file = fd2file(fd);
	return file->native_file.device;
}

int tcsetattr(int fildes, int optact, struct termios* tios)
{
	if(!fdvalid(fildes))
		return -1;

	FILE* file = fd2file(fildes);
	vfs_configure_int(file->native_file.device, "termios.c_iflag", tios->c_iflag);
	vfs_configure_int(file->native_file.device, "termios.c_oflag", tios->c_oflag);
	vfs_configure_int(file->native_file.device, "termios.c_lflag", tios->c_lflag);
	vfs_configure_int(file->native_file.device, "termios.c_cflag", tios->c_cflag);
	
	return 0;
}

int tcsendbreak(int x, int y)
{
	DSTUB;
}

speed_t cfgetispeed(const struct termios* tios)
{
	DSTUB;
}

speed_t cfgetospeed(const struct termios* tios)
{
	DSTUB;
}

int cfsetispeed(struct termios* tios, speed_t speed)
{
	DSTUB;
}

int cfsetospeed(struct termios* tios, speed_t speed)
{
	DSTUB;
}

int tcdrain(int val)
{
	DSTUB;
}

int tcflow(int x, int y)
{
	DSTUB;
}
