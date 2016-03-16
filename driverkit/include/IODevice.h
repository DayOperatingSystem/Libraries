#ifndef IODEVICE_H
#define IODEVICE_H

#include <dayos.h>

namespace IO
{

enum IO_STATUS
{
	IO_RUNNING,
	IO_STOPPED,
	IO_ERROR
};

class IODevice
{
	IO_STATUS m_status;
	
protected:
	void setStatus(IO_STATUS status) { m_status = status; }
	
public:
	IODevice() : m_status(IO_STOPPED) {}

	virtual const char* getName() = 0;
	virtual unsigned int getType() = 0;
	virtual bool handle(message_t& msg) = 0;
	virtual IO_STATUS getStatus() { return m_status; }
};
}

#endif // IODEVICE_H
