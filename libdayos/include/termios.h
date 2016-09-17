#ifndef __TERMIOS_H
#define __TERMIOS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BRKINT 0
#define ICRNL 1
#define IGNBRK 2
#define IGNCR 4
#define IGNPAR 8
#define INLCR 16
#define INPCK 32
#define ISTRIP 64
#define IUCLC 128
#define IXANY 256
#define IXOFF 512
#define IXON 1024
#define PARMRK 2048

#define VEOF 0
#define VEOL 1
#define VERASE 2
#define VKILL 3
#define VREPRINT 4
#define VINTR 5
#define VQUIT 6
#define VSUSP 7
#define VSTART 8
#define VSTOP 9
#define VLNEXT 10
#define VDISCARD 11
#define VMIN 12
#define VTIME 13
#define VSTATUS 14

#define NCCS 20

#define TCSANOW 0
#define TCSADRAIN 1
#define TCSAFLUSH 2

#define OPOST 1
#define ONLCR 2

#define ECHO 1
#define ECHOE 2
#define ECHOK 4
#define ECHONL 8
#define ICANON 16
#define IEXTEN 32
#define ISIG 64
#define NOFLSH 128
#define TOSTOP 256
#define XCASE 512

#define CSIZE 0x00000300
#define CS5 0x0
#define CS6 0x100
#define CS7 0x200
#define CS8 0x300

#define CREAD 0x800
#define PARENB 0x1000
#define PARODD 0x2000
#define HUPCL 0x4000
#define CLOCAL 0x8000

#define B0 0
#define B50 50
#define B75 75
#define B110 110
#define B134 134
#define B150 150
#define B200 200
#define B300 300
#define B600 600
#define B1200 1200
#define	B1800 1800
#define B2400 2400
#define B4800 4800
#define B9600 9600
#define B19200 19200
#define B38400 38400

typedef uint32_t cc_t;
typedef uint32_t speed_t;
typedef uint32_t tcflag_t;

struct termios
{
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_cc[NCCS];
};

speed_t cfgetispeed(const struct termios *);
speed_t cfgetospeed(const struct termios *);
int cfsetispeed(struct termios *, speed_t);
int cfsetospeed(struct termios *, speed_t);
int tcdrain(int);
int tcflow(int, int);
int tcflush(int, int);
int tcgetattr(int, struct termios *);
pid_t tcgetsid(int);
int tcsendbreak(int, int);
int tcsetattr(int, int, struct termios *);

#ifdef __cplusplus
}
#endif

#endif
