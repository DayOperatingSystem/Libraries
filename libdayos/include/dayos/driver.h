#ifndef __DRIVER_H
#define __DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include <kernelconfig.h>
#include <vfs.h>

#define DEVICE_REQUEST_MAGIC 0xDEADBEEF

/*
typedef enum
{
	FS_SIGNAL_MKDIR,
	FS_SIGNAL_OPEN = VFS_SIGNAL_OPEN,
	FS_SIGNAL_CLOSE,
	FS_SIGNAL_READ = VFS_SIGNAL_READ,
	FS_SIGNAL_WRITE = VFS_SIGNAL_WRITE,
	FS_SIGNAL_MOUNT,
	FS_SIGNAL_STAT = VFS_SIGNAL_STAT,
	FS_SIGNAL_OPEN_DIR = VFS_SIGNAL_OPEN_DIR,
	FS_SIGNAL_READ_DIR = VFS_SIGNAL_READ_DIR
} FS_SIGNALS;

/// Deprecated!
typedef enum
{
	DEVICE_READ = VFS_SIGNAL_READ,
	DEVICE_WRITE = VFS_SIGNAL_WRITE,
	DEVICE_IOCTL = VFS_SIGNAL_IOCTL
} DEVICE_ACTIONS;*/

struct device_request
{
	uint32_t magic;
	uint32_t size;
	uint8_t character;
};

#define FS_REQUEST_PATHLEN (MESSAGE_STRING_SIZE - 8)
struct fs_request
{
	uint32_t magic;
	uint32_t param;
	int8_t path[256];
};

#endif
