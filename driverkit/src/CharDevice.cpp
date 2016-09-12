#include <CharDevice.h>
#include <sys/stat.h>
#include <vfs.h>

bool IO::CharDevice::handle(message_t& msg)
{
	switch (msg.signal)
	{
		case VFS_SIGNAL_READ:
		{
			struct vfs_request* req = (struct vfs_request*) &msg.message;

			// FIXME: ONLY SUPPORTS LINE BUFFERING FOR NOW!
			m_currentRequests.push_front(ReadRequest(msg.sender, req->size, true));
			return true;
		}
		break;

		case VFS_SIGNAL_WRITE:
		{
			struct vfs_request* req = (struct vfs_request*) &msg.message;
			
			char* data = new char[req->size];
			read_message_stream(data, req->size, msg.sender);
			write(data, req->size);
			delete[] data;
			return true;
		}

		case VFS_SIGNAL_STAT:
		{
			struct stat* stat = (struct stat*) &msg.message;

			stat->st_dev = msg.receiver;
			stat->st_size = -1;

			msg.signal = SIGNAL_OK;
			send_message(&msg, msg.sender);
			return true;
		}
	}

	return false;
}

void IO::CharDevice::putch(char c)
{
	// FIXME: Only supports LINE BUFFERING!
	// Ignore input when nobody is listening
	if(m_currentRequests.size() > 0)
	{
		if(c == '\b')
		{
			if(!m_buffer.empty())
				m_buffer.pop_back();

			return;
		}
		else if(c == -1)
		{
			ReadRequest req = m_currentRequests.back();
			m_currentRequests.pop_back();
			m_buffer.clear();
			
			write_message_stream(&c, 1, req.receiver);
			return;
		}
		
		
		m_buffer.push_back(c);
		if(c == '\n')
		{
			ReadRequest req = m_currentRequests.back();
			m_currentRequests.pop_back();
			
			write_message_stream(&m_buffer[0], std::min(m_buffer.size(), req.size), req.receiver);
			m_buffer.clear();
		}
	}
}
