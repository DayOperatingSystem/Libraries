#include "FileSystem.h"
#include <driver.h>
#include <sys/stat.h>

const char* IO::FileSystem::getName()
{
	return nullptr;
}

unsigned int IO::FileSystem::getType()
{
	return 0;
}

bool IO::FileSystem::handle(message_t& msg)
{
	vfs_request* rq = (vfs_request*) &msg.message;
	switch (msg.signal)
	{
		case VFS_SIGNAL_OPEN:
		{
			if((rq->id = open(rq->path, (VFS_OPEN_MODES) rq->mode)) == 0)
				msg.signal = SIGNAL_FAIL;
			else
				msg.signal = SIGNAL_OK;

			send_message(&msg, msg.sender);
		}
		break;

		case VFS_SIGNAL_STAT:
		{
			struct stat* st = (struct stat*) &msg.message;
			if(!fstat(rq->id, st))
			{
				msg.signal = SIGNAL_FAIL;
				send_message(&msg, msg.sender);
				break;
			}

			st->st_dev = msg.receiver;

			msg.signal = SIGNAL_OK;
			send_message(&msg, msg.sender);
		}
			break;

		case VFS_SIGNAL_READ:
		{
			size_t sz = 0;
			if((sz = read(rq->id, msg.sender, rq->offset, rq->size)) == 0)
			{
				msg.signal = SIGNAL_FAIL;
				send_message(&msg, msg.sender);
				break;
			}
		}
		break;

		case VFS_SIGNAL_WRITE:
		{
			char* buffer = new char[rq->size];
			pid_t sender = msg.sender;

			read_message_stream(buffer, rq->size, msg.sender);
			write(rq->id, buffer, rq->offset, rq->size);

			delete[] buffer;
		}
		break;

		case VFS_SIGNAL_OPEN_DIR:
		{

		}
		break;

		case VFS_SIGNAL_READ_DIR:
		{

		}
		break;
		
		case VFS_SIGNAL_CREATE_DIRECTORY:
		{
			msg.signal = SIGNAL_FAIL;
			
			rq->id = createDirectory(rq->path, (VFS_OPEN_MODES) rq->mode);
			if(rq->id != 0)
			{
				msg.signal = SIGNAL_OK;
			}
			
			send_message(&msg, msg.sender);
		}
		break;
	}
}
