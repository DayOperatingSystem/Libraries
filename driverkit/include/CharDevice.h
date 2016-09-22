#ifndef CHARDEVICE_H
#define CHARDEVICE_H

#include <IODevice.h>
#include <vector>
#include <deque>

namespace IO
{

class CharDevice : IODevice
{
	struct ReadRequest
	{
		pid_t receiver;
		size_t size;
		bool linebuffer;
		
		ReadRequest(pid_t rec, size_t sz, bool line) 
			: receiver(rec),
			size(sz), 
			linebuffer(line) {}
	};
	
	std::deque<ReadRequest> m_currentRequests;
	std::vector<char> m_buffer;
protected:
	
	pid_t getNextRequestPID() { return m_currentRequests.begin()->receiver; }
	bool hasNextRequest() { return m_currentRequests.size() != 0; }
	
public:
	virtual const char* getName() { return "Generic Character Device"; }
	virtual unsigned int getType() { return 0; }
	virtual bool handle(message_t& msg);

	size_t getBufferSize() { return m_buffer.size(); }

	virtual void putch(char c, bool buffering);
	virtual size_t write(void* src, size_t size) = 0;
};
}
#endif // CHARDEVICE_H
