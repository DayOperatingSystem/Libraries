#include <dirent.h>
#include <dayos/message.h>
#include <stdlib.h>
#include <dayos/dayos.h>
#include <errno.h>
#include <string.h>
#include <dayos/driver.h>

int closedir(DIR* dir)
{
	free(dir->file);
	free(dir);
}

DIR* opendir(const char* path)
{
	DIR* dir = malloc(sizeof(DIR));
	
	dir->file = vfs_opendir(path);
	
	if(!dir->file)
	{
		free(dir);
		return NULL;
	}
	
	rewinddir(dir);	
	return dir;
}

struct dirent* readdir(DIR* dir)
{
	if(!dir) return NULL;

	struct vfs_file entry;
	if(vfs_readdir(dir->file, &entry, dir->next) != SIGNAL_OK)
		return NULL;
	
	dir->next = entry.child_nid;
	
	strncpy(dir->current.d_name, entry.path, sizeof(dir->current.d_name));
	return &dir->current;
}

long telldir(DIR* dir)
{
	return dir->current.d_ino;
}

void seekdir(DIR* dir, long off)
{
	dir->current.d_ino = off;
}

void rewinddir(DIR* dir)
{
	dir->next = dir->file->child_nid;
	//dir->current.d_ino = dir->file.offset;
}
