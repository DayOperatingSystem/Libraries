#ifndef BLOCKDEVICE_H
#define BLOCKDEVICE_H

#include "IODevice.h"
#include <vector>

namespace IO
{
class BlockDevice : public IODevice
{
	size_t m_blocksize;
	size_t m_numBlocks;
	size_t m_maxBuffer;
	size_t m_currentBlock;

	char* m_buffer;
protected:
	void setBlockCount(size_t sz) { m_numBlocks = sz; }
	void setBufferSize(size_t blocks) { m_maxBuffer = blocks; delete[] m_buffer; m_buffer = new char[blocks]; }

public:
	BlockDevice() : BlockDevice(512) {}
	BlockDevice(size_t blocksize) :
		m_blocksize(blocksize),
		IODevice(),
		m_numBlocks(0),
		m_maxBuffer(3),
		m_currentBlock(-1)
	{ m_buffer = new char[m_maxBuffer * m_blocksize]; }

	~BlockDevice() { delete[] m_buffer; }

	virtual const char* getName() { return "Generic Block Device"; }
	virtual unsigned int getType() { return 0; }
	virtual bool handle(message_t& msg);

	virtual bool readBlock(size_t offset, void* data) = 0;
	virtual bool writeBlock(size_t offset, void* data) = 0;

	size_t getBlocksize() { return m_blocksize; }
};
}

#endif // BLOCKDEVICE_H
