#include <dayos/vfs.h>
#include <dayos/service.h>
#include <dayos/dayos.h>
#include <dayos/message.h>
#include <string.h>
#include <sleep.h>
#include <dayos/driver.h>
#include <stdlib.h>
#include <errno.h>

struct vfs_file* vfs_open(const char* path, VFS_OPEN_MODES mode)
{
	pid_t pid = get_service_pid("vfs");

	if (pid == 0)
	{
		errno = ENOENT;
		return NULL;
	}

	struct vfs_file* file = malloc(sizeof(struct vfs_file));
	
	message_t* msg = malloc(sizeof(message_t));
	struct vfs_request* request = (struct vfs_request*) msg->message;
	struct vfs_file* msgfile = (struct vfs_file*) msg->message;
	
	strncpy(request->path, path, sizeof(request->path));
	request->mode = mode;

	msg->size = sizeof(struct vfs_request);
	msg->signal = VFS_SIGNAL_OPEN;
	send_message(msg, pid);
	
	if (receive_message_timeout(msg, pid, 100, 5) == MESSAGE_ERR_RECEIVE)
	{
		goto vfs_open_enoent;
	}

	if (msg->signal == SIGNAL_FAIL)
	{
		goto vfs_open_enoent;
	}

	*file = *msgfile;

	// Tell the FS driver (in case of a mounted device)
	if (msgfile->type == VFS_MOUNTPOINT)
	{
		msg->signal = VFS_SIGNAL_OPEN;
		strcpy(request->path, file->path);
		request->mode = mode;

		send_message(msg, file->device);

		if (receive_message_timeout(msg, file->device, 100, 5) ==
				MESSAGE_ERR_RECEIVE ||
				msg->signal != SIGNAL_OK)
		{
			goto vfs_open_enoent;
		}

		file->nid = request->id;
	}
	
	free(msg);
	return file;
	
vfs_open_enoent:
	errno = ENOENT;
	free(file);
	free(msg);
	return NULL;
}

int vfs_create_device(const char* path, unsigned int mode, unsigned int type)
{
	pid_t pid = get_service_pid("vfs");
	if(pid == 0)
		return SIGNAL_FAIL;
	
	message_t msg;
	msg.signal = VFS_SIGNAL_CREATE_DEVICE;

	struct vfs_request* request = (struct vfs_request*) &msg.message;
	
	request->magic = VFS_MAGIC;
	strcpy(request->path, path);
	request->mode = mode;
	request->param = type;
	
	send_message(&msg, pid);
	while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);
	return msg.signal;
}

size_t vfs_write(struct vfs_file* file, const void* data, size_t size)
{
	message_t msg;
	struct vfs_request* rq = (struct vfs_request*) &msg.message;

	msg.signal = VFS_SIGNAL_WRITE;

	rq->size = size;
	msg.size = sizeof(struct vfs_request);

	rq->id = file->nid;
	rq->offset = file->offset;
	strcpy(rq->path, file->path);
	send_message(&msg, file->device);

	size_t sz = write_message_stream(data, size, file->device);
	file->offset += sz;
	return sz;
}

size_t vfs_read(struct vfs_file* file, void* data, size_t size, VFS_BUFFER_MODES buffermode)
{
	message_t msg;
	struct vfs_request* rq = (struct vfs_request*) &msg.message;

	msg.signal = VFS_SIGNAL_READ;
	
	rq->size = size;
	msg.size = sizeof(struct vfs_request);

	rq->id = file->nid;
	rq->param = buffermode;
	rq->offset = file->offset;
	
	strcpy(rq->path, file->path);
	send_message(&msg, file->device);

	size_t sz = read_message_stream(data, size, file->device);
	file->offset += sz;
	
	return sz;
}

int vfs_mount_device(const char* src, const char* dest, const char* fsd, unsigned int mode)
{
	pid_t pid = get_service_pid("vfs");
	pid_t fsd_pid = get_service_pid(fsd);
	
	if(pid == 0 || fsd_pid)
		return SIGNAL_FAIL;
	
	message_t msg;
	msg.signal = VFS_SIGNAL_MOUNT_DEVICE;
	
	struct vfs_request* request = (struct vfs_request*) &msg.message;
	
	request->magic = VFS_MAGIC;
	
	strcpy(request->path, src);
	request->mode = mode;
	send_message(&msg, pid);
	
	strcpy(request->path, src);
	request->param = fsd_pid;
	strcpy(msg.message, dest);
	send_message(&msg, pid);
	
	while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);
	return msg.signal;
}

int vfs_mount_ramdisk(const char* dest, unsigned int mode)
{
	pid_t pid = get_service_pid("vfs");
	if(pid == 0)
		return SIGNAL_FAIL;
	
	message_t msg;
	msg.signal = VFS_SIGNAL_MOUNT_RAMDISK;
	
	struct vfs_request* request = (struct vfs_request*) &msg.message;
	
	request->magic = VFS_MAGIC;
	strcpy(request->path, dest);
	request->mode = mode;
	send_message(&msg, pid);
	
	while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);
	return msg.signal;
}

int vfs_stat(struct vfs_file* file, struct stat* stat)
{
	if(!file || !stat) return -1;
	
	message_t msg;
	struct vfs_request* rq = (struct vfs_request*) &msg.message;
	
	msg.signal = VFS_SIGNAL_STAT;
	rq->id = file->nid;
	strcpy(rq->path, file->path);
	
	send_message(&msg, file->device);
	while(receive_message(&msg, file->device) != MESSAGE_RECEIVED) sleep(1);
	
	if(msg.signal != SIGNAL_OK)
	{
		return -1;
	}
	
	struct stat* fs_stat = (struct stat*) &msg.message;
	*stat = *fs_stat;
	
	return 0;
}

struct vfs_file* vfs_opendir(const char* path)
{
	pid_t pid = get_service_pid("vfs");

	if (pid == 0)
	{
		errno = ENOENT;
		return NULL;
	}

	struct vfs_file* file = malloc(sizeof(struct vfs_file));
	message_t* msg = malloc(sizeof(message_t));
	struct vfs_request* request = (struct vfs_request*) msg->message;
	struct vfs_file* msgfile = (struct vfs_file*) msg->message;

	strncpy(request->path, path, sizeof(request->path));

	msg->size = sizeof(struct vfs_request);
	msg->signal = VFS_SIGNAL_OPEN_DIR;
	send_message(msg, pid);
	
	if (receive_message_timeout(msg, pid, 100, 5) == MESSAGE_ERR_RECEIVE)
	{
		goto vfs_opendir_enoent;
	}

	if (msg->signal == SIGNAL_FAIL)
	{
		goto vfs_opendir_enoent;
	}

	*file = *msgfile;

	// Tell the FS driver (in case of a mounted device)
	if (msgfile->type == VFS_MOUNTPOINT)
	{
		msg->signal = VFS_SIGNAL_OPEN_DIR;
		strcpy(request->path, file->path);

		send_message(msg, file->device);

		if (receive_message_timeout(msg, file->device, 100, 5) ==
				MESSAGE_ERR_RECEIVE ||
				msg->signal != SIGNAL_OK)
		{
			goto vfs_opendir_enoent;
		}

		file->nid = request->id;
		file->child_nid = request->param;
	}
	
	free(msg);
	return file;
	
vfs_opendir_enoent:
	errno = ENOENT;
	free(file);
	free(msg);
	return NULL;
}

int vfs_readdir(struct vfs_file* dir, struct vfs_file* dest, int id)
{
	if(!dir || !dest)
		return -1;
	
	message_t msg;
	struct vfs_request* rq = (struct vfs_request*) &msg.message;
	msg.signal = VFS_SIGNAL_READ_DIR;
	
	rq->param = id;
	rq->id = dir->nid;
	
	strcpy(rq->path, dir->path);
	
	send_message(&msg, dir->device);
	while(receive_message(&msg, dir->device) != MESSAGE_RECEIVED) sleep(1);
	
	if(msg.signal != SIGNAL_OK)
	{
		return -1;
	}
	
	struct vfs_file* f = (struct vfs_file*) &msg.message;
	*dest = *f;
	return 0;
}

int vfs_mkdir(const char* path, VFS_ACCESS_MODES mode)
{
	message_t* msg = malloc(sizeof(message_t));
	
	struct vfs_request* rq = (struct vfs_request*) &msg->message;
	struct vfs_file* msgfile = (struct vfs_file*) &msg->message;
	
	msg->signal = VFS_SIGNAL_CREATE_DIRECTORY;
	rq->mode = mode;
	
	strncpy(rq->path, path, sizeof(rq->path));
	
	pid_t pid = get_service_pid("vfs");

	if (pid == 0)
	{
		errno = ENOENT;
		return NULL;
	}
	
	send_message(msg, pid);
	if (receive_message_timeout(msg, pid, 100, 5) ==
				MESSAGE_ERR_RECEIVE ||
				msg->signal != SIGNAL_OK)
		{
			free(msg);
			return SIGNAL_FAIL;
		}
		
	// Tell the FS driver (in case of a mounted device)
	if (msgfile->type == VFS_MOUNTPOINT)
	{
		uint32_t device = msgfile->device;
		msg->signal = VFS_SIGNAL_CREATE_DIRECTORY;
		
		memmove(rq->path, msgfile->path, strlen(msgfile->path));
		rq->mode = mode;

		send_message(msg, device);

		if (receive_message_timeout(msg, device, 100, 5) ==
				MESSAGE_ERR_RECEIVE ||
				msg->signal != SIGNAL_OK)
		{
			free(msg);
			errno = ENOENT;
			return SIGNAL_FAIL;
		}
	}
	
	free(msg);
	return SIGNAL_OK;
}

int vfs_configure(pid_t pid, const char* key, const char* value)
{
	message_t* msg = (message_t*) malloc(sizeof(message_t));
	struct vfs_config_request* rq = (struct vfs_config_request*) &msg->message;
	
	strncpy(rq->key, key, sizeof(rq->key));
	strncpy(rq->value, value, sizeof(rq->value));
	msg->signal = VFS_SIGNAL_CONFIGURE;
	
	send_message(msg, pid);
	
	if(receive_message_timeout(msg, pid, 100, 5) == MESSAGE_ERR_RECEIVE)
		msg->signal = SIGNAL_FAIL;
	
	free(msg);
	return msg->signal;
}

int vfs_configure_int(pid_t pid, const char* key, int value)
{
	char buf[32];
	sprintf(buf, "%d", value);

	return vfs_configure(pid, key, buf);
}

