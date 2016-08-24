#ifndef __STAT_H
#define __STAT_H

#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#include <dayos/vfs.h>

struct stat
{
	mode_t st_mode;
	ino_t st_ino;
	dev_t st_dev;
	dev_t st_rdev;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	off_t st_size;
	struct timespec st_atim;
	struct timespec st_mtim;
	struct timespec st_ctim;
	blksize_t st_blksize;
	blkcnt_t st_blocks;

	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
};

#define S_IRWXU (00700)
#define S_IRUSR (00400)
#define S_IWUSR (00200)
#define S_IXUSR (00100)
#define S_IRWXG (00070)
#define S_IRGRP (00040)
#define S_IWGRP (00020)
#define S_IXGRP (00010)
#define S_IRWXO (00007)
#define S_IROTH (00004)
#define S_IWOTH (00002)
#define S_IXOTH (00001)

#define S_IFMT (0xFF)

#define S_IFREG ((mode_t) VFS_REGULAR)
#define S_IFCHR ((mode_t) VFS_CHARACTER_DEVICE)
#define S_IFIFO ((mode_t) VFS_FIFO)
#define S_IFBLK ((mode_t) VFS_BLOCK_DEVICE)
#define S_IFDIR ((mode_t) VFS_DIRECTORY)
#define S_IFLNK ((mode_t) VFS_LINK)
#define S_IFSOCK ((mode_t) VFS_SOCKET)

#ifdef __cplusplus
extern "C" {
#endif

int chmod(const char* name, mode_t mode);
int fchmod(int fd, mode_t mode);
int fstat(int fd, struct stat* stat);
int lstat(const char* name, struct stat* stat);
int mkdir(const char* name, mode_t mode);
int mkfifo(const char* name, mode_t mode);
int mknod(const char* name, mode_t mode, dev_t dev);
int stat(const char* name, struct stat* stat);
mode_t umask(mode_t mode);

#ifdef __cplusplus
}
#endif
	
#endif
