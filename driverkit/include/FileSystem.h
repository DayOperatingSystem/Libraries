#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <memory>
#include <IODevice.h>
#include <dayos.h>
#include <vfs.h>

typedef int file_handle_t;

namespace IO
{
class FileSystem : public IO::IODevice
{
public:

	virtual const char* getName();
	virtual unsigned int getType();
	virtual bool handle(message_t& msg);
	
	virtual file_handle_t open(const char* path, VFS_OPEN_MODES mode) = 0;
	virtual void close(file_handle_t handle) = 0;
	virtual size_t read(file_handle_t, pid_t receiver, size_t offset, size_t size) = 0;
	virtual size_t write(file_handle_t file, void* data, size_t offset, size_t size) = 0;
	virtual bool remove(file_handle_t file) = 0;
	virtual bool move(file_handle_t dir, const char* path) = 0;
	virtual bool fstat(file_handle_t handle, struct stat* st) = 0;

	virtual file_handle_t opendir(const char* path, ino_t* id, ino_t* nid) = 0;
	virtual file_handle_t readdir(file_handle_t dir, size_t idx, struct vfs_file* dest) = 0;
	virtual bool removeDirectory(file_handle_t file) = 0;
	virtual file_handle_t createDirectory(const char* path, VFS_OPEN_MODES mode) = 0;

	virtual void changeOwner(file_handle_t node, uid_t user) = 0;
	virtual void changeMode(file_handle_t node, mode_t mode) = 0;
	
	/*
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
	virtual void changeMode(Node& node, mode_t mode) = 0;*/
};
}
#endif // FILESYSTEM_H
