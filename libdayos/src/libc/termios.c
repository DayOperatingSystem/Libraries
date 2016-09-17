#include <termios.h>
#include <dayos/dayos.h>

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

int tcflush(int x, int y)
{
	DSTUB;
}

int tcgetattr(int val, struct termios* tios)
{
	DSTUB;
}

pid_t tcgetsid(int val)
{
	DSTUB;
}

int tcsendbreak(int x, int y)
{
	DSTUB;
}

int tcsetattr(int x, int y, struct termios* tios)
{
	DSTUB;
}
