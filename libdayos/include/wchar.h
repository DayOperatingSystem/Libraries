#ifndef __WCHAR_H
#define __WCHAR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef __WCHAR_TYPE__ wchar_t;
 
int wcwidth(wchar_t);

 #ifdef __cplusplus
}
#endif
 
#endif
