#ifndef __FCNTL_EXTRA_H
#define __FCNTL_EXTRA_H

#include <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif

FILE* fd2file(int fd);

/**
 * @brief Checks if the given fd is valid.
 * 
 * Sets errno in case the fd is not valid.
 * 
 * @param fd The file descriptor to check.
 * @return 1 if valid, 0 otherwise.
 */
int fdvalid(int fd);

#ifdef __cplusplus
}
#endif

#endif
