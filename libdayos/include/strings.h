#ifndef __STRINGS_H
#define __STRINGS_H

#ifdef __cplusplus
extern "C" {
#endif

int strcasecmp(const char*, const char*);
int strncasecmp(const char*, const char*, size_t);

#ifdef __cplusplus
}
#endif

#endif