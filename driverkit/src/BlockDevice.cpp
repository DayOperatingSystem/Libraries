#include "BlockDevice.h"
#include <sys/stat.h>
#include <vfs.h>

bool IO::BlockDevice::handle(message_t& msg)
{
	switch(msg.signal)
	{
		case VFS_SIGNAL_READ:
		{
			struct vfs_request* request = (struct vfs_request*) &msg.message;
			pid_t sender = msg.sender;
			size_t size = msg.size;
			size_t blocks = (msg.size / m_blocksize) + (size % m_blocksize) ? 1 : 0;
			size_t blockOffset = request->offset / m_blocksize;

			//debug_printf("size: %d blocks: %d blockOffset: %d\n", size, blocks, blockOffset);

			// Don't read over the end of the device
			if(blockOffset + blocks >= m_numBlocks || blocks > m_maxBuffer)
			{
				msg.signal = SIGNAL_FAIL;
				send_message(&msg, msg.sender);
				return true;
			}

			// FIXME: DON'T HARDCODE!
			if(blockOffset < m_currentBlock || blockOffset > (m_currentBlock + m_maxBuffer))
			{
				blocks = m_maxBuffer;
				for (; blocks > 0; blocks--)
				{
					//debug_printf("Loading block: %d to %d\n", blockOffset + blocks - 1, (blocks - 1) * m_blocksize);
					readBlock(blockOffset + blocks - 1, &m_buffer[(blocks - 1) * m_blocksize]);
				}

				m_currentBlock = blockOffset;
			}

			// debug_printf("Writing %d %d %d\n", request->offset, size, sender);
			write_message_stream(&m_buffer[request->offset % m_blocksize], size, sender);
		}
		return true;

		case VFS_SIGNAL_WRITE:
			return true;

		case VFS_SIGNAL_STAT:
		{
			struct stat* stat = (struct stat*)&msg.message;

			stat->st_dev = msg.receiver;
			stat->st_size = (m_blocksize * m_numBlocks);

			msg.signal = SIGNAL_OK;
			send_message(&msg, msg.sender);
			return true;
		}
	}
	return false;
}
