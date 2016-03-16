#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <memory>
#include <IODevice.h>
#include <dayos.h>

namespace IO
{
class FileSystem : public IO::IODevice
{
public:

	class Node
	{};

	class File : public Node
	{};

	class Directory : public Node
	{};

	virtual const char* getName();
	virtual unsigned int getType();
	virtual bool handle(message_t& msg);

	virtual std::shared_ptr<File> open(const char* path, VFS_OPEN_MODES mode) = 0;
	virtual size_t read(File& file, void* data, size_t offset, size_t size) = 0;
	virtual size_t write(File& file, void* data, size_t offset, size_t size) = 0;
	virtual bool remove(File& file) = 0;
	virtual bool move(Node& dir, const char* path) = 0;

	virtual std::shared_ptr<Directory> opendir(const char* path) = 0;
	virtual std::shared_ptr<Node> readdir(Directory& dir, size_t idx) = 0;
	virtual bool removeDirectory(Directory& file) = 0;
	virtual std::shared_ptr<Directory> createDirectory(const char* path) = 0;

	virtual void changeOwner(Node& node, uid_t user) = 0;
	virtual void changeMode(Node& node, mode_t mode) = 0;
};
}
#endif // FILESYSTEM_H
