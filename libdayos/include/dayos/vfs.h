#ifndef VFS_H
#define VFS_H

#include <stddef.h>
#include <kernelconfig.h>

typedef enum
{
	VFS_MODE_RO = 1,
	VFS_MODE_WO = 2,
	VFS_MODE_RW = VFS_MODE_RO | VFS_MODE_WO
} VFS_OPEN_MODES;

typedef enum
{
	VFS_SIGNAL_CREATE_DEVICE = 0,
	VFS_SIGNAL_OPEN = 1,
	VFS_SIGNAL_MOUNT_DEVICE = 2,
	VFS_SIGNAL_MOUNT_RAMDISK = 3,
	VFS_SIGNAL_OPEN_DIR = 4,
	VFS_SIGNAL_READ_DIR = 5,
	VFS_SIGNAL_READ = 6,
	VFS_SIGNAL_WRITE = 7,
	VFS_SIGNAL_STAT = 8,
	VFS_SIGNAL_IOCTL = 9,
	VFS_SIGNAL_CREATE_DIRECTORY = 10
} VFS_SIGNALS;

typedef enum
{
	VFS_CHARACTER_DEVICE = 0,
	VFS_BLOCK_DEVICE = 1,
	VFS_MOUNTPOINT = 2,
	VFS_DIRECTORY = 4,
	VFS_REGULAR = 8,
	VFS_FIFO = 16,
	VFS_LINK = 32,
	VFS_SOCKET = 64
} DEVICE_TYPES;

typedef enum
{
	VFS_LINE_BUFFER = 0,
	VFS_BLOCK_BUFFER = 1,
	VFS_NO_BUFFER = 2
} VFS_BUFFER_MODES;

typedef enum
{
	VFS_ACCESS_READ = 0x1,
	VFS_ACCESS_WRITE = 0x2,
	VFS_ACCESS_EXECUTE = 0x4
} VFS_ACCESS_MODES;

#include <sys/types.h>
#include <stdint.h>

// One vfs_request has to fit into one message.
// The size of the flags is 6*4byte on 32bit machines => 24bytes in total.
#define VFS_FILENAME_SIZE (MESSAGE_STRING_SIZE - 24)

// Magic number to check for sanity
#define VFS_MAGIC 0xDEADBEEF

// Structures for IA32
struct vfs_request
{
	int8_t path[VFS_FILENAME_SIZE];
	uint32_t mode;
	uint32_t param;
	uint32_t size;
	uint32_t offset;
	uint32_t magic;
	uint32_t id;
};

struct vfs_file
{
	int8_t path[VFS_FILENAME_SIZE];
	pid_t device;

	uint32_t type;
	uint32_t guid;
	uint32_t uid;
	ino_t nid;
	ino_t child_nid; /// The node id of the first child if it is a directory, the next file in the directory if it is a file
	size_t offset;
	size_t size;
};

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration of stat
struct stat;

/**
 * @brief Opens an existing file or creates a new one if it doesn't exist.
 * 
 * @param path The filepath to open.
 * @param mode The mode to request.
 */
struct vfs_file* vfs_open(const char* path, VFS_OPEN_MODES mode);

/**
 * @brief A fread version that operations on DayOS native files.
 * 
 * @param file The file to read from.
 * @param data The data memory to read to.
 * @param size The size of the data to read.
 * @param buffermode The intended buffer mode.
 * @return The size in bytes that was actually read.
 */
size_t vfs_read(struct vfs_file* file, void* data, size_t size, VFS_BUFFER_MODES buffermode);

/**
 * @brief A fwrite version that operations on DayOS native files.
 * 
 * @param file The file to write to.
 * @param data The data to write.
 * @param size The size of the data to read.
 * @return The size in bytes that was actually written.
 */
size_t vfs_write(struct vfs_file* file, const void* data, size_t size);

/**
 * @brief Creates a device descriptor in the VFS that can be opened for reading
 * or writing.
 * @param path The path to the device file.
 * @param mode The mode of the device (@see VFS_OPEN_MODES)
 * @param type The type of the device (@see DEVICE_TYPES)
 *
 * @return SIGNAL_OK if everything went well, SIGNAL_FAIL if not.
 */
int vfs_create_device(const char* path, unsigned int mode, unsigned int type);
int vfs_mount_device(const char* src, const char* dest, const char* fsd, unsigned int mode);
int vfs_mount_ramdisk(const char* dest, unsigned int mode);

struct vfs_file* vfs_opendir(const char* path);
int vfs_readdir(struct vfs_file* dir, struct vfs_file* dest, int id);
int vfs_stat(struct vfs_file* file, struct stat* stat);

int vfs_mkdir(const char* path, VFS_ACCESS_MODES mode);

#ifdef __cplusplus
}
#endif

#endif
